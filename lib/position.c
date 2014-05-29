#include <stdlib.h>
#include <stdio.h>
#include "./position.h"

position_t* copy_position(position_t* src) {
  position_t* dest;

  dest = malloc(sizeof(position_t));
  dest->white = copy_pos(src->white);
  dest->black = copy_pos(src->black);
  dest->castle = src->castle;
  dest->enpassant = src->enpassant;
  dest->active_p = src->active_p;
  dest->half_move = src->half_move;
  dest->full_move = src->full_move;
  return dest;
}

pos_t* copy_pos(pos_t* src) {
  pos_t* dest;

  dest = malloc(sizeof(pos_t));
  dest->pieces = src->pieces;
  dest->piece[PAWN] = src->piece[PAWN];
  dest->piece[KNIGHT] = src->piece[KNIGHT];
  dest->piece[BISHOP] = src->piece[BISHOP];
  dest->piece[ROOK] = src->piece[ROOK];
  dest->piece[QUEEN] = src->piece[QUEEN];
  dest->piece[KING] = src->piece[KING];
  return dest;
}

/*
 * Frees the positions allocated memory
 */

void free_position(position_t* p) {
  if(p==NULL) return;
  if(p->white!=NULL) free(p->white);
  if(p->black!=NULL) free(p->black);
  free(p);
}

/*
 * Fetches the piece at the given location, if any
 */

piece_t position_piece(position_t* p, square_t s) {
  piece_t piece;

  if((piece = pos_piece(p->white, s)) != NO_PIECE) return piece | WHITE;
  if((piece = pos_piece(p->black, s)) != NO_PIECE) return piece | BLACK;
  return NO_PIECE;
}

/*
 * Fetches the piece at the given location, if any
 */

piece_t pos_piece(pos_t* p, square_t s) {
  bitboard_t sq;
  piece_t piece;

  sq = 1ull << s;
  if(! (sq & p->pieces)) return NO_PIECE; // empty square
  for(piece = PAWN; piece <= KING; piece++) {
    if(sq & p->piece[piece]) return piece;
  }
  return NO_PIECE;
}

/*
 * Debugs the position to standard output
 */

void position_debug(position_t* p, int verbose) {
  square_t i,j;
  piece_t piece;

  if(verbose) {
    printf("verbose output enabled \n");
    printf("white: \n");
    printf("all pieces . . . . . 0x%.16llx \n", p->white->pieces);
    printf("pawns  . . . . . . . 0x%.16llx \n", p->white->piece[PAWN]);
    printf("knights  . . . . . . 0x%.16llx \n", p->white->piece[KNIGHT]);
    printf("bishops  . . . . . . 0x%.16llx \n", p->white->piece[BISHOP]);
    printf("rooks  . . . . . . . 0x%.16llx \n", p->white->piece[ROOK]);
    printf("queens . . . . . . . 0x%.16llx \n", p->white->piece[QUEEN]);
    printf("king . . . . . . . . 0x%.16llx \n\n", p->white->piece[KING]);
    printf("black: \n");
    printf("all pieces . . . . . 0x%.16llx \n", p->black->pieces);
    printf("pawns  . . . . . . . 0x%.16llx \n", p->black->piece[PAWN]);
    printf("knights  . . . . . . 0x%.16llx \n", p->black->piece[KNIGHT]);
    printf("bishops  . . . . . . 0x%.16llx \n", p->black->piece[BISHOP]);
    printf("rooks  . . . . . . . 0x%.16llx \n", p->black->piece[ROOK]);
    printf("queens . . . . . . . 0x%.16llx \n", p->black->piece[QUEEN]);
    printf("king . . . . . . . . 0x%.16llx \n\n", p->black->piece[KING]);
    printf("meta-inf: \n");
    printf("castle w,k . . . . . %d \n", 0 != (p->castle & CASTLE_WHITE_KINGSIDE));
    printf("castle w,q . . . . . %d \n", 0 != (p->castle & CASTLE_WHITE_QUEENSIDE));
    printf("castle b,k . . . . . %d \n", 0 != (p->castle & CASTLE_BLACK_KINGSIDE));
    printf("castle b,q . . . . . %d \n", 0 != (p->castle & CASTLE_BLACK_QUEENSIDE));
    printf("enpassant  . . . . . %s \n", SQUARE_STR(p->enpassant));
    printf("active_p . . . . . . %c \n\n", p->active_p==WHITE? 'w' : 'b');
    printf("half_move  . . . . . %d \n", p->half_move);
    printf("full_move  . . . . . %d \n\n", p->full_move);
  }

  for(j=0; j<8; j++) {
    for(i=A8-8*j; i <= H8-8*j; i++) {
      piece = position_piece(p,i);
      printf("%c", piece_debug_glyph[piece]);
    }
    printf("\n");
  }
}

/*
 * Debugs the position to standard output
 */

void pos_debug(pos_t* p) {
  square_t i,j;
  piece_t piece;

  for(j=0; j<8; j++) {
    for(i=A8-8*j; i <= H8-8*j; i++) {
      piece = pos_piece(p,i);
      printf("%c", piece_debug_glyph[piece]);
    }
    printf("\n");
  }
}
