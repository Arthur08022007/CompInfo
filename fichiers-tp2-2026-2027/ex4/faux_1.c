
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "faux_1.h"

int search_pattern_faux_1(char *pattern, char *message) {
  if (pattern==NULL || message==NULL)
    return -1;
  
  int patternLength = strlen(pattern);
  int msgLength = strlen(message);
  
  if (msgLength<patternLength)
    return -1;
  
	int i;
	for (i = 0; i + patternLength < msgLength; i++)
	  {
	    int j;
	    for (j = 0; message[i+j] == pattern[j] && j < patternLength; j++);
	    if (j == patternLength)
			return i;
		}

	return -1;
}
