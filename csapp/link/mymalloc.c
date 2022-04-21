/**
 * from CSAPP code/link/interpose/mymalloc.c
 */

#ifdef COMPILETIME
#include <stdio.h>
#include <malloc.h>

// malloc wrapper function
void *mymalloc(size_t size) {
  void *ptr = malloc(size);
  printf("malloc(%ld) = %p\n", size, ptr);
  return ptr;
}

// free wrapper function
void myfree(void *ptr) {
  free(ptr);
  printf("free(%p)\n", ptr);
}
#endif

#ifdef LINKTIME
#include <stdio.h>

void *__real_malloc(size_t size);
void __real_free(void *ptr);

// malloc wrapper function
void *__wrap_malloc(size_t size) {
  void *ptr = __real_malloc(size);
  printf("malloc(%ld) = %p\n", size, ptr);
  return ptr;
}

// free wrapper function
void __wrap_free(void *ptr) {
  __real_free(ptr);
  printf("free(%p)\n", ptr);
}
#endif

#ifdef RUNTIME
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

// malloc wrapper function
void *malloc(size_t size) {
  void *(*mallocp)(size_t size) = NULL;
  char *error = NULL;

  mallocp = dlsym(RTLD_NEXT, "malloc"); // get address of libc malloc
  if ((error = dlerror()) != NULL) {
    perror(error);
    exit(EXIT_FAILURE);
  }
  void *ptr = mallocp(size);  // call libc malloc

  /**
   * printf() might call malloc() once
   * use this to avoid infinite recursion: malloc() -> printf() -> malloc()
   */
  static int is_first_malloc = 1;
  if (is_first_malloc) {
    is_first_malloc = 0;
    printf("malloc(%ld) = %p\n", size, ptr);
    is_first_malloc = 1;
  }
  return ptr;
}

// free wrapper function
void free(void *ptr) {
  void (*freep)(void *ptr) = NULL;
  char *error = NULL;

  if (!ptr) return;

  freep = dlsym(RTLD_NEXT, "free"); // get address of libc free
  if ((error = dlerror()) != NULL) {
    perror(error);
    exit(EXIT_FAILURE);
  }
  freep(ptr); // call libc free
  printf("free(%p)\n", ptr);
}
#endif