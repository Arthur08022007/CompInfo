#ifndef _SET_H
#define _SET_H

typedef struct Set_t Set;

Set *setCreate(int size);
void setFree(Set *s);
void setInsert(Set *s, char *key);
int  setContains(Set *s, char *key);
void setPrintStat(Set *s);

#endif
