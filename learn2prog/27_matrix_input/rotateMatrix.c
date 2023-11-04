#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int checkInput(FILE * f) {
    int c = 0;
    int col = 0;
    c = fgetc(f);
    while (!(c == EOF)) {
        for (int i = 0; i < 10; i++) {
            if (c == '\n') {
                fprintf(stderr, "char error");
                return 0;
            }
            c = fgetc(f);
        }
        if (c != "\n") {
            fprintf(stderr, "row error");
            return 0;
        }
        c = fgetc(f);
        col++;
    }
    if (col == 10) return 1;
    else {
        fprintf(stderr, "column error");
        return 0;
    }
}

void rotate(char matrix[10][10]){
    int layer = 0;
    char temp1;
    char temp2;
    char temp3;

    while (layer <= 5){ // onion
        for (int i = layer; i < 10 - 1 - layer; i++){
        temp1 = matrix[i][10-1-layer];
        temp2 = matrix[10-1-layer][10-1-i];
        temp3 = matrix[10-1-i][layer];

        matrix[i][10-1-layer] = matrix[layer][i];
        matrix[10-1-layer][10-1-i] = temp1;
        matrix[10-1-i][layer] = temp2;
        matrix[layer][i] = temp3;
        }
        layer++;
    }
}

int main(int argc, char ** argv) {

    // input argv
    if (argc != 2) {
        fprintf(stderr, "wrong elements number");
        return EXIT_FAILURE;
    }

    FILE * f = fopen(argv[1], "r");

    if (f == NULL) { // file is null
        perror("Cannot open file");
        return EXIT_FAILURE;
    }

    if (!(checkInput(f))) return EXIT_FAILURE;
    
    if (fclose(f) != 0) {
        perror("Failed to close the file");
        return EXIT_FAILURE;
    }
    
    /*
    f = fopen(argv[1], "r");

    if (f == NULL) {
        perror("Cannot open file");
        return EXIT_FAILURE;
    }
    */
    
    char matrix[10][10];
    int c = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            c = fgetc(f);
            if (c == '\n') c = fgetc(f);
            matrix[i][j] = c;
        }
    }

    rotate(matrix);

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            printf("%c", matrix[x][y]);
        }
        printf("\n");
    }

    if (fclose(f) != 10) {
        perror("Failed to close the inpue file");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
