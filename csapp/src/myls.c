/**
 * @file myls.c
 * @author Jax (jaxvanyang@gmail.com)
 * @brief list files, just like simplified ls
 * @version 0.1
 * @date 2022-04-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

struct Node {
  char *name;
  struct Node *next;
};

extern int errno;
static int columns = 80;

static struct Node *get_node(char *name);
static struct Node *insert(struct Node *head, char *name);
void ls(char *path);

int main(int argc, char *argv[]) {
  char *COLUMNS = getenv("COLUMNS");
  if (COLUMNS) columns = atoi(COLUMNS);

  if (argc == 1) {
    ls(".");
    return 0;
  } else if (argc == 2) {
    ls(argv[1]);
    return 0;
  }

  int i;
  for (i = 1; i < argc; ++i) {
    printf("%s:\n", argv[i]);
    ls(argv[i]);
    putchar('\n');
  }
}

static struct Node *get_node(char *name) {
  struct Node *node = malloc(sizeof(struct Node));
  node->name = name;
  node->next = NULL;
  return node;
}

static struct Node *insert(struct Node *head, char *name) {
  struct Node *ret = malloc(sizeof(struct Node));
  ret->name = name;
  ret->next = head;
  return ret;
}

void ls(char *path) {
  DIR *dirp = opendir(path);
  if (!dirp) {
    fprintf(stderr, "myls: cannot access %s: %s\n", path, strerror(errno));
    return;
  }

  struct Node *end = get_node(NULL);
  struct Node *head = end;
  int max_len = 0;
  struct dirent *direntp = NULL;
  while ((direntp = readdir(dirp)) != NULL) {
    char *name = direntp->d_name;
    if (name[0] == '.') continue; // skip hidden files
    int len = strlen(name);
    if (len > max_len) max_len = len;
    
    head = insert(head, name);
  }

  // col_cnt maybe 0
  int col_cnt = columns / (max_len + 1);
  if (col_cnt == 0) col_cnt = 1;
  int i = 0;

  while (head != end) {
    i = 0;
    // print each line
    while (head != end && i < col_cnt) {
      int len = strlen(head->name);
      len = max_len + 1 - len;  // if name is too long, len may be negative
      printf("%s", head->name);
      for (int j = 0; j < len; ++j) putchar(' '); // padding when len is positive

      ++i;
      head = head->next;
    }
    putchar('\n');
  }

  closedir(dirp);
}
