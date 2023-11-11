#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"
#include <assert.h>

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "File not found");
        assert (f != NULL);
        return NULL;
    }

    counts_t * count = createCounts();
    char * line = NULL;
    size_t sz = 0;
    char * value = NULL;
    char * ptr1 = NULL;

    while (getline(&line, &sz, f) != EOF) {
        ptr1 = strchr(line, '\n'); // will not work on win
        *ptr1 = '\0';
        value = lookupValue(kvPairs, line);
        addCount(count, value);
    }

    free(line);

    if (fclose(f) != 0) {
        fprintf(stderr, "Unable to close file");
        return NULL;
    }

    return count;
}

int main(int argc, char ** argv) {
    //WRITE ME (plus add appropriate error checking!)
    //read the key/value pairs from the file named by argv[1] (call the result kv)
    if (argc < 3) {
        fprintf(stderr, "Wrong input number");
        return EXIT_FAILURE;
    }

    kvarray_t * kv = readKVs(argv[1]);

    counts_t * c = NULL;

    //count from 2 to argc (call the number you count i)
    for (int i = 2; i < argc; i++) {
        //count the values that appear in the file named by argv[i], using kv as the key/value pair
        //   (call this result c)
        c = countFile(argv[i], kv);
        //compute the output file name from argv[i] (call this outName)
        char * outname = computeOutputFileName(argv[i]);
        //open the file named by outName (call that f)
        FILE * f = fopen(outname, "w");
        //print the counts from c into the FILE f
        printCounts(c, f);
        //close f
        if (fclose(f) != 0) {
            fprintf(stderr, "Unable to close file");
            return EXIT_FAILURE;
        }

        //free the memory for outName and c
        free(outname);
        freeCounts(c);
    }

    //free the memory for kv
    freeKVs(kv);
    return EXIT_SUCCESS;
}