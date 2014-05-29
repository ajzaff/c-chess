#include <stdio.h>
#include "../bitboard.c"

int main() {
  int i;

  for(i=FILE_A; i <= FILE_H; i++) {
    printf("debug bitboard mask file %c: \n",'A'+i);
    bitboard_debug(BITBOARD_MASK[i]);
  }
  for(i=RANK_1; i <= RANK_8; i++) {
    printf("debug bitboard mask rank %d: \n",i-7);
    bitboard_debug(BITBOARD_MASK[i]);
  }
  printf("debug bitboard no mask: \n");
  bitboard_debug(BITBOARD_MASK[NO_MASK]);
  printf("debug bitboard mask universe: \n");
  bitboard_debug(BITBOARD_MASK[UNIVERSE]);
  printf("debug bitboard mask center: \n");
  bitboard_debug(BITBOARD_MASK[CENTER]);
  printf("debug bitboard mask rim: \n");
  bitboard_debug(BITBOARD_MASK[RIM]);
  printf("debug bitboard mask corner: \n");
  bitboard_debug(BITBOARD_MASK[CORNER]);
  printf("debug finished \n");
}
