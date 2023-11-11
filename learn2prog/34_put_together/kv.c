#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include <assert.h>

kvpair_t * readKV(FILE * f) {
    char * line = NULL;
    size_t sz = 0;

    //Get whole line and store it into "line"
    if (getline(&line, &sz, f) == EOF) {
        free(line);  //free line if we've reached EOF
        return NULL;
    }

    //Find first occurrence to = and set ptr to point there
    char * ptr1 = strchr(line, '=');
    if (ptr1 == NULL) {
        free(line);
        return NULL;
    }

    //Create bounds of key and value,
    //line will point to key and ptr1 at '\0' - previously '='
    char * ptr2 = strstr(line, "\r\n");
    //should be strchr(line, '\n') in online emacs, but my terminal is wsl so this works properly
    //strchr(line, '\r') works for me too
    if (ptr2 == NULL) {
        free(line);
        return NULL;
    }

    * ptr1 = '\0';
    * ptr2 = '\0';  //"key\0value\0"

    kvpair_t * retPair = malloc(sizeof(*retPair));
    retPair->key = line;
    ptr1++;
    retPair->value = ptr1;
    return retPair;
}


kvarray_t * readKVs(const char * fname) {
    FILE * f = fopen(fname, "r");
    if (f == NULL) {
        fprintf(stderr, "File not found");
        return NULL;
    }

    int line_num = 0;
    kvarray_t * retAry = malloc(sizeof(*retAry));
    kvpair_t * pairInAry = NULL;
    retAry->list_len = 0;
    retAry->list = NULL;

    while ((pairInAry = readKV(f)) != NULL) {
        retAry->list = realloc(retAry->list, (line_num + 1) * sizeof(*retAry->list));
        retAry->list[line_num] = pairInAry;
        line_num++;
    }

    retAry->list_len = line_num;
    assert (fclose(f) == 0);
    free(pairInAry);  // malloced in readKV
    return retAry;
}

void freeKVs(kvarray_t * pairs) {
    for (int i = 0; i < pairs->list_len; i++) {
        free(pairs->list[i]->key);
        free(pairs->list[i]);
    }
    free(pairs->list);
    free(pairs);
}

void printKVs(kvarray_t * pairs) {
    for (int i = 0; i < pairs->list_len; i++) {
        printf("key = '%s' value = '%s'\n", pairs->list[i]->key, pairs->list[i]->value);
    }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
    for (int i = 0; i < pairs->list_len; i++) {
        if (strcmp(pairs->list[i]->key, key) == 0) {
            return pairs->list[i]->value;
        }
    }
    return NULL;
}
