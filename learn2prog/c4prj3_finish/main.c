#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

void free_input(deck_t ** input, size_t num){
    for (size_t i=0; i<num; i++){
        free_deck(input[i]);
    }
    free(input);
}

int main(int argc, char ** argv) {
    // Check command line arguments/report errors
    if (argc > 3 || argc < 2) {
        fprintf(stderr, "Wrong number of input arguments");
        return EXIT_FAILURE;
    }

    unsigned trials = 10000;
    if (argc == 3) {
        trials = atoi(argv[2]);
    }

    // Open the input file and read the hands in it
    FILE * f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "File not found");
        return EXIT_FAILURE;
    }

    future_cards_t * fc = malloc(sizeof(*fc));
    fc->decks = NULL;
    fc->n_decks = 0;
    size_t n_hands = 0;
    deck_t ** input = read_input(f, &n_hands, fc);

    // Create a deck with the remaining cards
    deck_t * remaining_cards = build_remaining_deck(input, n_hands);

    // Create an array to count how many times each hand wins
    unsigned win_array[n_hands + 1];
    for (int i = 0; i < n_hands + 1; i++) {
        win_array[i] = 0;
    }

    // Do each Monte Carlo trial (repeat num_trials times)
    for (int i = 0; i < trials; i++) {
        // Shuffle the deck of remaining cards
        shuffle(remaining_cards);

        // Assign unknown cards from the shuffled deck
        future_cards_from_deck(remaining_cards, fc);

        // Use compare_hands (from Course 3) to figure out which hand won
        int inc_array_at = 0;
        int index = 0;
        for (int x = 1; x < n_hands; x++) {
            if (compare_hands(input[index], input[x]) == 0) inc_array_at = n_hands;
            if (compare_hands(input[index], input[x]) < 0) {
                inc_array_at = x;
                index = x;
            }
        }
        // Increment the win count for the winninghand
        win_array[inc_array_at]++;
    }
    // Print your results
    for (size_t i = 0; i < n_hands; i++) {
        printf("Hand %zu won %u / %u times (%.2f%%)\n", i, win_array[i], trials, (double)win_array[i] / (double)trials * 100);
    }
    // Printf one more line for the ties
    printf("There were %u ties.\n", win_array[n_hands]);

    // Free any memory you allocated
    free_input(input, n_hands);
    free_deck(remaining_cards);
    for (size_t i = 0; i < fc->n_decks; i++) free(fc->decks[i].cards);
    free(fc->decks);
    free(fc);

    // Close any open files
    if (fclose(f) != 0) {
        fprintf(stderr, "Cannot close file");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}