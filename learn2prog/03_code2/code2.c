#include <stdio.h>

int printTriangle(int size) {
    // Start with starCount being 0
    int starCount = 0;
    // Count from 0 (inclusive) to size (exclusive) for each number i that you count
    for (int i=0; i<size; i++) {
        // Count from 0 (inclusive) to i (inclusive) for each number j that you count
        for (int j=0; j<=i; j++) {
            // Print a "*"
            printf("*");
            // Increment starCount
            starCount ++;
        }
        // When you finish counting j, print a new line
        printf("\n");
    }
    // When you finish counting i, your answer is starCount
    return starCount;
}

int main(void) {
    int numStars;
    int m = 4;
    int n = 7;
    printf("Here is a reiangle with height %d\n", m);
    numStars = printTriangle(m);
    printf("That triangle had %d total stars\n", numStars);
    printf("Here is a reiangle with height %d\n", n);
    numStars = printTriangle(n);
    printf("That triangle had %d total stars\n", numStars);
    return 0;
}