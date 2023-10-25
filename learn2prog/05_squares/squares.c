
#include <stdio.h>
#include <stdlib.h>

// Determines if coord is in range between
// offset (inclusive) and offset + size (exclusive)
int isInRange(int coord, int offset, int size) {
    // If in range, return 1
    if (coord >= offset && coord < offset+size) {
        return 1;
    }else {
        return 0;
    }
}

// Determines if coord is at border of offset or offset + size
int isBorder(int coord, int offset, int size) {
    if (coord == offset || coord == offset+size) {
        return 1;
    }else {
        return 0;
    }
}

// Max
int max(int a, int b) {
    return (a > b? a: b);
}

// Min
int min(int a, int b) {
    return (a < b? a: b);
}

// Main
void squares(int size1, int x_offset, int y_offset, int size2) {
    // Compute max of size1 and x_offset + size2, call it w
    int w = max(size1, x_offset + size2);
    // Compute max of size1 and y_offset + size2, call it h
    int h = max(size1, y_offset + size2);
    // Count from 0 to h, call it y
    for (int y = 0; y <= h; y++) {
        // Count from 0 to w, call it x
        for (int x = 0; x <= w; x++) {
            // Check if either
                // x is between x_offset and x_offset + size2 AND
                // y is equals to either y_offset or y_offset + size2 - 1
            // OR
                // y is between y_offset and y_offset + size2 AND
                // x is equals to either x_offset or x_offset + size2 - 1
            if (((x >= x_offset && x < x_offset + size2) &&\
                 (y == y_offset || y == y_offset + size2 - 1)) ||\
                ((y >= y_offset && y < y_offset + size2) &&\
                 (x == x_offset || x == x_offset + size2 - 1))) {
                    // If so ,print a "*"
                    printf("*");
            }else {
            // If not, check if either
                // x is less than size1 AND (y is either 0 or size1 - 1)
            // OR
                // y is less than size1 AND (x is either 0 or size1 - 1)
                if ((x < size1 && (y == 0 || y == size1 - 1)) ||\
                    (y < size1 && (x == 0 || x == size1 - 1))) {
                        // If so ,print a "*"
                        printf("#");
                }else {
                    // Else print a " "
                    printf(" ");
                }
            }
        }
        // When finish counting x, print a newline
        printf("\n");
    }
}

int main(void) {
    squares(9, 2, 3, 4);
    return 0;
}