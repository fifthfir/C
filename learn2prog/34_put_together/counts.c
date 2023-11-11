#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
  counts_t * ret_cot = malloc(sizeof(*ret_cot));
  ret_cot->count_array = NULL;
  ret_cot->ary_size = 0;
  ret_cot->unk_count = 0;
  return ret_cot;
}

void addCount(counts_t * c, const char * name) {
    if (name == NULL) {
        c->unk_count++;
        return;
    }

    //if (name != NULL)
    c->count_array = realloc(c->count_array, (c->ary_size + 1) * sizeof(*c->count_array));
    for (int i = 0; i < c->ary_size; i++) {
        if (strcmp(c->count_array[i]->value, name) == 0) {
            c->count_array[i]->count++;
            return;
        }
    }

    char * entry = strdup(name);
    c->count_array[c->ary_size] = malloc(sizeof(*c->count_array[c->ary_size]));
    c->count_array[c->ary_size]->value = entry;
    c->count_array[c->ary_size]->count = 1;
    c->ary_size++;
    return;
}

void printCounts(counts_t * c, FILE * outFile) {
  for (int i = 0; i < c->ary_size; i++) {
    fprintf(outFile, "%s : %d\n", c->count_array[i]->value, c->count_array[i]->count);
  }
  if (c->unk_count > 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unk_count);
  }
  return;
}

void freeCounts(counts_t * c) {
  for (int i = 0; i < c->ary_size; i++) {
    free(c->count_array[i]->value);
    free(c->count_array[i]);
  }
  free(c->count_array);
  free(c);
  return;
}