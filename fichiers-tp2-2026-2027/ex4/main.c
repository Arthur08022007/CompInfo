#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_searchpattern.h"
#include "bon_1.h"
#include "bon_2.h"
#include "faux_1.h"
#include "faux_2.h"
#include "faux_3.h"
#include "faux_4.h"
#include "faux_5.h"
#include "faux_6.h"
#include "faux_7.h"

int main(void)
{
  printf("--------- TEST SEARCH PATTERN 1 (code correct) ---------\n");
  if (test_search_pattern(search_pattern_bon_1)) {
    printf("Test reussi !\n");
  } else {
    printf("Test rate !\n");
  }

  printf("--------- TEST SEARCH PATTERN 2 (code correct) ---------\n");
  if (test_search_pattern(search_pattern_bon_2)) {
    printf("Test reussi !\n");
  } else {
    printf("Test rate !\n");
  }

  printf("--------- TEST SEARCH PATTERN 3 (code incorrect) ---------\n");
  if (!test_search_pattern(search_pattern_faux_1)) {
    printf("Test reussi !\n");
  } else {
    printf("Test rate !\n");
  }

  printf("--------- TEST SEARCH PATTERN 4 (code incorrect) ---------\n");
  if (!test_search_pattern(search_pattern_faux_2)) {
    printf("Test Reussi !\n");
  } else {
    printf("Test rate !\n");
  }

  printf("--------- TEST SEARCH PATTERN 5 (code incorrect) ---------\n");
  if (!test_search_pattern(search_pattern_faux_3)) {
    printf("Test reussi !\n");
  } else {
    printf("Test rate !\n");
  }

  printf("--------- TEST SEARCH PATTERN 6 (code incorrect) ---------\n");
  if (!test_search_pattern(search_pattern_faux_4)) {
    printf("Test reussi !\n");
  } else {
    printf("Test rate !\n");
  }

  printf("--------- TEST SEARCH PATTERN 7 (code incorrect) ---------\n");
  if (!test_search_pattern(search_pattern_faux_5)) {
    printf("Test reussi !\n");
  } else {
    printf("Test rate !\n");
  }

  printf("--------- TEST SEARCH PATTERN 8 (code incorrect) ---------\n");
  if (!test_search_pattern(search_pattern_faux_6)) {
    printf("Test reussi !\n");
  } else {
    printf("Test rate !\n");
  }

  printf("--------- TEST SEARCH PATTERN 9 (code incorrect) ---------\n");
  if (!test_search_pattern(search_pattern_faux_7)) {
    printf("Test reussi !\n");
  } else {
    printf("Test rate !\n");
  }

  return (0);
}
