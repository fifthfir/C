#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

size_t max(int * letters, size_t n){
  int maxCount = letters[0];
  int maxIdx = 0;

  for (size_t i = 0; i < n; i++) {
    if ( letters[i] > maxCount ) {
      maxCount = letters[i];
      maxIdx = i;
    }
  }
  return maxIdx;
}

int decrypt(FILE * f) {
  int c;
  int letters[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  while ((c = fgetc(f))!= EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      letters[c] = letters[c] + 1;
    }
  }
  size_t maxElement = max(letters, 26);
  int ans;

  if (maxElement >= 4) {
    ans = maxElement - 4;
  }else {
    ans = 26 - (4 - maxElement);
  }
  return ans;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1],"r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  size_t key = decrypt(f);
  printf("%zu\n", key);
  return EXIT_SUCCESS;
}