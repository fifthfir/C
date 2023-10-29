#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void){
  int array1[] = {-2};
  if (maxSeq(array1, 1) != 1){return EXIT_FAILURE;}
  int array2[] = {2, 2, 2, 3};
  if (maxSeq(array2, 4) != 2){return EXIT_FAILURE;}
  int array3[] = {2, -3, 5, 6, 8};
  if (maxSeq(array3, 5) != 4){return EXIT_FAILURE;}
  int array4[] = {2};
  if (maxSeq(array4, 1) != 1){return EXIT_FAILURE;}
  int array5[] = {2, 4, 3, 6, 10, 15, -1, 7, 8, 2};
  if (maxSeq(array5, 10) != 4){return EXIT_FAILURE;}
  int array6[] = {1, 2, 3, 2};
  if (maxSeq(array6, 4) != 3){return EXIT_FAILURE;}
  int array7[] = {};
  if (maxSeq(array7, 0) != 0){return EXIT_FAILURE;}
  return EXIT_SUCCESS;
}
