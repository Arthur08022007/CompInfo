
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "set.h"

typedef struct Node_t {
  char *key;
  struct Node_t *next;
} Node;

struct Set_t {
  Node **array;
  unsigned int arraySize;
  unsigned int nKeys;
};

Set *setCreate(int size) {
  Set *s = malloc(sizeof(Set));
  if (s == NULL)
    exit(-1);
  s -> array = calloc(size, sizeof(Node *));
  if (s -> array == NULL)
    exit(-1);
  s -> arraySize = size;
  s -> nKeys = 0;
  return s;
}

void setFree(Set *s) {
  for (unsigned int i = 0; i < s -> arraySize; i++) {
    Node *p = s -> array[i];
    while (p != NULL) {
      Node *nextp = p -> next;
      free(p);
      p = nextp;
    }
  }
  free(s -> array);
  free(s);
}

/* djb2 (http://www.cse.yorku.ca/~oz/hash.html) */

static size_t hash(Set *s, char *key) {
  size_t hash = 5381;

  while (*key != '\0') {
    hash = ((hash << 5) + hash) + *key; // hash = hash * 33 + *key
    key++;
  }
  return hash % (s -> arraySize);
}

int setContains(Set *s, char *key) {
  size_t hc = hash(s, key);
  for (Node *p = s -> array[hc]; p != NULL; p = p -> next) {
    if (strcmp(key, p -> key) == 0) {
      return 1;
    }
  }
  return 0;
}

// A completer

void setInsert(Set *s, char *key) {
  // ...
}
