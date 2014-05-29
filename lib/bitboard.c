#include <stdio.h>
#include <stdlib.h>
#include "./bitboard.h"

/*
 * Takes a bitboard and outputs it to standard
 * output as a simple grid of `marks` and `blanks`
 */

void bitboard_debug(bitboard_t b) {
  square_t i,j;

  for(j=0; j<8; j++) {
    for(i=A8-8*j; i <= H8-8*j; i++) {
      if(b & (0x1ull<<i)) {
        printf("%c", BITBOARD_DEBUG_MARK);
      }
      else {
        printf("%c", BITBOARD_DEBUG_BLANK);
      }
    }
    printf("\n");
  }
}
