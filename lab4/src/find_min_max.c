#include "find_min_max.h"
#include <stdio.h>
#include <limits.h>

struct MinMax GetMinMax(int *array, unsigned int begin, unsigned int end) {
  struct MinMax min_max;
  min_max.min = INT_MAX;
  min_max.max = INT_MIN;

  while (begin < end)
  {
    //if (array[begin] == 1041)
     // printf("array%d = %d\n", begin, array[begin]);
    if (array[begin] > min_max.max)
      min_max.max = array[begin];
    if (array[begin] < min_max.min)
      min_max.min = array[begin];
    begin++;
  }
  // your code here
  return min_max;
}
