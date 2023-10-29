#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert ( c.value >= 2 && c.value <= VALUE_ACE );
  assert ( c.suit >= SPADES && c.suit <= CLUBS );
}

const char * ranking_to_string(hand_ranking_t r) {
  if ( r == STRAIGHT_FLUSH ){
    return "STRAIGHT_FLUSH";
  }else if ( r == FOUR_OF_A_KIND ){
    return "FOUR_OF_A_KIND";
  }else if ( r == FULL_HOUSE ){
    return "FULL_HOUSE";
  }else if ( r == FLUSH ){
    return "FLUSH";
  }else if ( r == STRAIGHT ){
    return "STRAIGHT";
  }else if ( r == THREE_OF_A_KIND ){
    return "THREE_OF_A_KIND";
  }else if ( r == TWO_PAIR ){
    return "TWO_PAIR";
  }else if ( r == PAIR ){
    return "PAIR";
  }else if ( r == NOTHING ){
    return "NOTHING";
  }
  exit(EXIT_FAILURE);
}

char value_letter(card_t c) {
  char ret;
  int val = c.value;
  if ( val < 10 && val > 1 ){
    ret = '0' + val;
  }else if ( val == 10 ){
    ret = '0';
  }else if( val == VALUE_JACK ){
    ret = 'J';
  }else if( val == VALUE_QUEEN ){
    ret = 'Q';
  }else if( val == VALUE_KING ){
    ret = 'K';
  }else if( val == VALUE_ACE ){
    ret = 'A';
  }
  return ret;
}


char suit_letter(card_t c) {
  suit_t suit = c.suit;
  char ret;
  if ( suit == SPADES ){
    ret = 's';
  }else if ( suit == HEARTS ){
    ret = 'h';
  }else if ( suit == DIAMONDS ){
    ret = 'd';
  }else if ( suit == CLUBS ){
    ret = 'c';
  }
  return ret;
}

void print_card(card_t c) {
  char val = value_letter(c);
  char suit = suit_letter(c);
  printf("%c%c", val, suit);
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  if ( value_let == 'J' ){
    temp.value = VALUE_JACK;
  }else if ( value_let == 'Q' ){
    temp.value = VALUE_QUEEN;
  }else if ( value_let == 'K' ){
    temp.value = VALUE_KING;
  }else if ( value_let == 'A' ){
    temp.value = VALUE_ACE;
  }else if ( value_let == '0'){
    temp.value = 10;
  }else {
    temp.value = value_let - '0';
  }
  
  if ( suit_let == 's' ){
    temp.suit = SPADES;
  }else if ( suit_let == 'h' ){
    temp.suit = HEARTS;
  }else if ( suit_let == 'd' ){
    temp.suit = DIAMONDS;
  }else if ( suit_let == 'c' ){
    temp.suit = CLUBS;
  }
  assert_card_valid(temp);
  return temp;
}

card_t card_from_num(unsigned c) {
  assert ( c >= 0 && c < 52 );
  card_t temp;
  int suit_num = c / 13;
  int value_num = c % 13;
  if ( suit_num == 0 ){
    temp.suit = SPADES;
  }else if ( suit_num == 1 ){
    temp.suit = HEARTS;
  }else if ( suit_num == 2 ){
    temp.suit = DIAMONDS;
  }else {
    temp.suit = CLUBS;
  }
  temp.value = value_num + 2;
  return temp;
}
