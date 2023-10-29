#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned ans){
  if ( power(x, y) != ans ){
    exit(EXIT_FAILURE);
  }
}

void main(void){
  run_check(2, 0, 1);
  run_check(1, 1, 1);
  run_check(0, 0, 1);
  run_check(-3, 2, 9);
  run_check(-2, 3, -8);
  exit(EXIT_SUCCESS);
}
