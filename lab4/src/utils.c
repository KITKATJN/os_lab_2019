#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
void GenerateArray(int *array, unsigned int array_size, unsigned int seed) {
  srand(seed);
  for (int i = 0; i < (int)array_size; i++) {
    array[i] = rand() / 100000;
    printf("arrgen = %d\n", array[i]);
    //printf("Gen array = %d\n", array[i]);
  }
}