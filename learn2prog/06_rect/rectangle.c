#include <stdio.h>
#include <stdlib.h>

// Help function
int min (int a, int b) {
  return (a < b? a: b);
}

int max(int a, int b) {
  return (a > b? a: b);
}

// Rectangle struct
typedef struct {
  int x;
  int y;
  int width;
  int height;
} rectangle;

// Canonicalize rectangle
rectangle canonicalize(rectangle r) {
  if (r.width < 0) {
    r.x += r.width;
    r.width = -r.width;
  }
  if (r.height < 0) {
    r.y += r.height;
    r.height = -r.height;
  }
  return r;
}

rectangle intersection(rectangle r1, rectangle r2) {
  // Canonicalize
  r1 = canonicalize(r1);
  r2 = canonicalize(r2);

  // Helper numbers
  int r1_xm = r1.x + r1.width;
  int r2_xm = r2.x + r2.width;
  int r1_ym = r1.y + r1.height;
  int r2_ym = r2.y + r2.height;
  int sum_2_width = r1.width + r2.width;
  int sum_2_height = r1.height + r2.height;
  int max_xm = max(r1_xm, r2_xm);
  int max_ym = max(r1_ym, r2_ym);
  int min_x = min(r1.x, r2.x);
  int max_x = max(r1.x, r2.x);
  int min_y = min(r1.y, r2.y);
  int max_y = max(r1.y, r2.y);
  int distance_x = max_xm - min_x;
  int distance_y = max_ym - min_y;
  rectangle new_r;

  // Conditions
  // 1 - No overlap: (1) seperated; (2) corner touch corner
  if (((sum_2_width < max_xm - min_x) || (sum_2_height < max_ym - min_y)) ||\
      ((sum_2_width == max_xm - min_x) && (sum_2_height == max_ym - min_y))) {
    new_r.width = 0;
    new_r.height = 0;
  }else {
    new_r.x = max_x;
    new_r.y = max_y;
    new_r.width = sum_2_width - distance_x;
    new_r.height = sum_2_height - distance_y;
  }
  return new_r;
}

// No need to modify code below
void printRectangle(rectangle r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }else {
    printf("(%d,%d) to (%d,%d)\n", r.x, r.y, r.x + r.width, r.y + r.height);
  }
}

int main(void) {
  rectangle r1;
  rectangle r2;
  rectangle r3;
  rectangle r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  printf("r2 is ");
  printRectangle(r2);

  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  printf("r4 is ");
  printRectangle(r4);

  // Test everything with r1
  rectangle i = intersection(r1,r1);
  printf("intersection(r1,r1): ");
  printRectangle(i);

  i = intersection(r1,r2);
  printf("intersection(r1,r2): ");
  printRectangle(i);
  
  i = intersection(r1,r3);
  printf("intersection(r1,r3): ");
  printRectangle(i);

  i = intersection(r1,r4);
  printf("intersection(r1,r4): ");
  printRectangle(i);

  // Test everything with r2
  i = intersection(r2,r1);
  printf("intersection(r2,r1): ");
  printRectangle(i);

  i = intersection(r2,r2);
  printf("intersection(r2,r2): ");
  printRectangle(i);
  
  i = intersection(r2,r3);
  printf("intersection(r2,r3): ");
  printRectangle(i);

  i = intersection(r2,r4);
  printf("intersection(r2,r4): ");
  printRectangle(i);

  //test everything with r3
  i = intersection(r3,r1);
  printf("intersection(r3,r1): ");
  printRectangle(i);

  i = intersection(r3,r2);
  printf("intersection(r3,r2): ");
  printRectangle(i);
  
  i = intersection(r3,r3);
  printf("intersection(r3,r3): ");
  printRectangle(i);

  i = intersection(r3,r4);
  printf("intersection(r3,r4): ");
  printRectangle(i);

  //test everything with r4
  i = intersection(r4,r1);
  printf("intersection(r4,r1): ");
  printRectangle(i);

  i = intersection(r4,r2);
  printf("intersection(r4,r2): ");
  printRectangle(i);
  
  i = intersection(r4,r3);
  printf("intersection(r4,r3): ");
  printRectangle(i);

  i = intersection(r4,r4);
  printf("intersection(r4,r4): ");
  printRectangle(i);

  return EXIT_SUCCESS;
}