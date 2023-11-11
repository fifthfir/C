#include <stdio.h>
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

void add_card_to(deck_t * deck, card_t c) {
  card_t * card = malloc(sizeof(* card));
  card->value = c.value;
  card->suit = c.suit;

  deck->cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(deck->cards));
  deck->cards[deck->n_cards] = card;
  deck->n_cards++;
  return;
}

card_t * add_empty_card(deck_t * deck) {
  card_t * empty_card = malloc(sizeof(* empty_card));
  empty_card->value = 0;
  empty_card->suit = 0;

  deck->cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(deck->cards));
  deck->cards[deck->n_cards] = empty_card;
  deck->n_cards++;
  return empty_card;
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t * ret_deck = malloc(sizeof(*ret_deck));
  ret_deck->cards = NULL;
  ret_deck->n_cards = 0;
  for (unsigned i = 0; i <52; i++) {
    card_t this_card = card_from_num(i);
    if (deck_contains(excluded_cards, this_card) == 0) {
        add_card_to(ret_deck, this_card);
    }
  }
  return ret_deck;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
    deck_t * deck_has_cards = malloc(sizeof(* deck_has_cards));
    deck_has_cards->cards = NULL;
    deck_has_cards->n_cards = 0;

    deck_t * this_hand;
    card_t * this_card;

    for (size_t i = 0; i < n_hands; i++) {
        this_hand = hands[i];
        for (size_t j = 0; j < this_hand->n_cards; j++) {
            this_card = this_hand->cards[j];
            if (this_card->value != 0 && !deck_contains(deck_has_cards, * this_card)) {
                add_card_to(deck_has_cards, * this_card);
            }
        }
    }
    deck_t * ret_deck;
    ret_deck = make_deck_exclude(deck_has_cards);
    free(deck_has_cards);
    return ret_deck;
}

void free_deck(deck_t * deck) {
    for (size_t i = 0; i < deck->n_cards; i++) {
        free(deck->cards[i]);
    }
    free(deck->cards);
    free(deck);
    return;
}