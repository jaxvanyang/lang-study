/**
 * from CSAPP code/link/dll.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int x[2] = {1, 2};
int y[2] = {3, 4};
int z[2];

int main() {
  void *handle = NULL;
  void (*addvec)(int *x, int *y, int *z, int n) = NULL;
  char *error = NULL;

  // Dynamically load the shared library containing addvec()
  handle = dlopen("./libvector.so", RTLD_LAZY);
  if (!handle) {
    perror(dlerror());
    exit(EXIT_FAILURE);
  }

  // Get a pointer to the addvec() function we just loaded
  addvec = dlsym(handle, "addvec");
  if ((error = dlerror()) != NULL) {
    perror(error);
    exit(EXIT_FAILURE);
  }

  // Now we can call addvec() just like any other function
  addvec(x, y, z, 2);
  printf("z = [%d %d]\n", z[0], z[1]);

  // Unload the shared library
  if (dlclose(handle)) {
    perror(dlerror());
    exit(EXIT_FAILURE);
  }

  return 0;
}