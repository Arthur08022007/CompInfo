#ifndef DICT_H
#define DICT_H

typedef struct Dict_t Dict;

// create dictionary
Dict *dictCreate(int m);

// free dictionary (including all keys but not the values)
void dictFree(Dict *d);

// search key in dictionary
void *dictSearch(Dict *d, char *key);

// Check if key is in dictionary
int dictContains(Dict *d, char *key);

// insert value in dictionary key (a copy of the key is created)
void dictInsert(Dict *d, char *key, void *value);

#endif
