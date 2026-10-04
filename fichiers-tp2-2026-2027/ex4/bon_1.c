
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bon_1.h"

int search_pattern_bon_1(char *pattern, char *message) {
    int patternlength = strlen(pattern);
    int messlength = strlen(message);
    int i = 0;
    int j = 0;
    int debut = 0;
    while (i < patternlength && j < messlength) {
        /*On regarde quand la premiere lettre du pattern apparait dans le message*/
        while (pattern[i] != message[j] && j < messlength)
            j++;
        if (pattern[i] == message[j])
            debut = j;
        /*On parcourt la partie du message afin de voir si toutes les lettres du pattern apparaissent*/
        while (pattern[i] == message[debut] && i < patternlength && debut < messlength) {
            i++;
            debut++;
        }
        if (i != patternlength) {
            i = 0;
            j++;
        }
    }
    if (i != patternlength)
        return -1;
    else
        return j;
}
