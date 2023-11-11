#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "future.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
    if (index < fc->n_decks) {
        fc->decks[index].cards = realloc(fc->decks[index].cards, sizeof(*fc->decks[index].cards) * (1 + fc->decks[index].n_cards));
        fc->decks[index].cards[fc->decks[index].n_cards] = ptr;
        fc->decks[index].n_cards++;
    }
    if (index >= fc->n_decks) {
        while (index >= fc->n_decks) {
            fc->decks = realloc(fc->decks, sizeof(* fc->decks) * (fc->n_decks + 1));
            fc->decks[fc->n_decks].cards = NULL;
            fc->decks[fc->n_decks].n_cards = 0;
            fc->n_decks++;
        }
        fc->decks[index].cards = realloc(fc->decks[index].cards, sizeof(*fc->decks[index].cards) * (1 + fc->decks[index].n_cards));
        fc->decks[index].cards[fc->decks[index].n_cards] = ptr;
        fc->decks[index].n_cards++;
    }
    return;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
    if (deck->n_cards < fc->n_decks) {
        fprintf(stderr, "No enough cards");
        return;
    }
    for (size_t i = 0; i < fc->n_decks; i++) {
        if (fc->decks[i].n_cards == 0) {
            continue;
        }else {
            for (size_t j = 0; j < fc->decks[i].n_cards; j++) {
            *(fc->decks[i].cards[j]) = *(deck->cards[i]);
            }
        }

    }
    return;
}