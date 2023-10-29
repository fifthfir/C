#include <stdio.h>
#include <stdlib.h>

int max(int a, int b){return (a > b? a: b);}

size_t maxSeq(int * array, size_t n){
  if (n == 0){return 0;}
  size_t maxLen = 1;
  size_t count = 1;
  int last = array[0];
  for (int i=1; i<n; i++){
    if (array[i] > last){
      count ++;
      maxLen = max(maxLen, count);
    }else{
      count = 1;
    }
    last = array[i];
  }
  return maxLen;
}
