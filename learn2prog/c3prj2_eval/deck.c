../c3prj1_deck/deck.c#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void print_hand(deck_t * hand){
  for ( size_t i = 0; i < hand->n_cards; i++ ){
    print_card(*hand->cards[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  for ( size_t i = 0; i < d->n_cards; i++ ){
    card_t ci = *d->cards[i];
    if ( ci.value == c.value && ci.suit == c.suit ){
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  card_t temp;
  int times = rand() % 10 + 1;
  for ( int i = 0; i < times; i++ ){
    size_t c1 = rand() % d->n_cards;
    size_t c2 = rand() % d->n_cards;
    temp = *d->cards[c1];
    *d->cards[c1] = *d->cards[c2];
    *d->cards[c2] = temp;
  }
}

void assert_full_deck(deck_t * d) {
  card_t temp;
  for ( int i = 0; i < 52; i++ ){
    temp = card_from_num(i);
    assert ( deck_contains(d, temp) );
  }
}