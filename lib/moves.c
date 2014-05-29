#include <stdio.h>
#include <stdlib.h>
#include "./moves.h"
#include "./position.c"

/*
 * Parses a move from a plain string;
 * a simple move grammar is defined as follows:
 * move := piece (file) (rank) (x) file rank		# not pawns
 * 	 | file (x file) rank (promo)			# pawns
 * piece := [NBRQK]
 * promo := =[NBRQ]
 * file := [abcdefgh]
 * rank := [12345678]
 *
 * A position `p` is provided to validate the move
 * and resolve or throw any ambiguity conflicts;
 * 
 * If successful, the function returns a pointer to a move,
 * however, the function is not always successful;
 * If an error occurs during the parse, a `parse_m_err_t`
 * error state will be returned. For a full listing of these
 * consult the `moves.h` header;
 */

parse_m_t parse_move(char* str, position_t* p) {
  parse_m_t pm_u;
  move_t* move;
  piece_t piece, capture, promotion;
  mask_key_t file1,file2,rank1,rank2;
  square_t src,dest;
  char buf[3];

  piece = parse_piece(str,0);
  if(piece == NO_PIECE) { // pawn move
    file1 = parse_file(str,1);
    if(*str == 'x') { // pawn capture
      str++;
      file2 = parse_file(str,1);
      rank2 = parse_rank(str,1);
      dest = MASK_KEY_SQUARE(file2,rank2);
      src = dest - (file2 > 8+file1? 9 : 7);
      capture = position_piece(p,dest);
      if(capture == NO_PIECE) { // illegal // TODO XXXXXXXXXXXXXXXX EN PASSANT!
        fprintf(stderr, "error: illegal capture: no piece on '%s'",SQUARE_STR(dest)); // TODO
	pm_u.err = PARSE_MOVE_ILLEGAL;
        return pm_u; // TODO
      }
      if(capture & COLOR == p->active_p) { // illegal
        fprintf(stderr, "error: illegal capture: can't take one of your own: on '%s'",SQUARE_STR(dest));
	pm_u.err = PARSE_MOVE_ILLEGAL;
        return pm_u;
      }
      piece = PAWN | p->active_p;
    }
    else { // pawn advance
      rank2 = parse_rank(str,1);
      file2 = file1;
      rank1 = rank2-8;
      dest = MASK_KEY_SQUARE(file2,rank2);
      src = MASK_KEY_SQUARE(file1,rank1);
      piece = position_piece(p,src);
      if(piece == NO_PIECE) {
        if(rank2 != (p->active_p == WHITE? RANK_4 : RANK_5)) { // illegal
          fprintf(stderr, "error: illegal move: '%s'",SQUARE_STR(dest));
          pm_u.err = PARSE_MOVE_ILLEGAL;
          return pm_u;
        }
        rank1 -= 8;
        src = MASK_KEY_SQUARE(file1,rank1);
        piece = position_piece(p,src);
        if(piece == NO_PIECE) {
          fprintf(stderr, "error: illegal move: '%s'",SQUARE_STR(dest));
          pm_u.err = PARSE_MOVE_ILLEGAL;
          return pm_u;
        }
      }
      piece = PAWN | p->active_p;
    }
    promotion = parse_promo(str,0);
  }
  else { // not pawn move
    
  }

  // allocate the move
  move = malloc(sizeof(move_t));
  move->src = src;
  move->dest = dest;
  move->old_ep = NO_SQUARE;
  move->new_ep = NO_SQUARE;
  move->via_ep = 0;
  move->moving = piece;
  move->promoted = promotion;
  move->captured = capture;
  pm_u.move = move;
  return pm_u;
}

piece_t parse_piece(char* str,int fatal) {
}

piece_t parse_promo(char* str,int fatal) {
}

mask_key_t parse_file(char* str,int fatal) {
}

mask_key_t parse_rank(char* str,int fatal) {
}

void move_make(move_t* m, position_t* p) {
}

void move_unmake(move_t* m, position_t* p) {
}

void move_str(move_t* m, char* str) {
}

void move_debug(move_t* m, int verbose) {
  char str[3];

  if(verbose) {
    printf("verbose output enabled \n");
    printf("src  . . . . . . . . %s \n", SQUARE_STR(m->src));
    printf("dest . . . . . . . . %s \n", SQUARE_STR(m->dest));
    printf("old e.p. . . . . . . %s \n", SQUARE_STR(m->old_ep));
    printf("new e.p. . . . . . . %s \n", SQUARE_STR(m->new_ep));
    printf("via e.p. . . . . . . %d \n", m->via_ep);
    printf("moving . . . . . . . %c \n", piece_debug_glyph[m->moving]);
    printf("promoted . . . . . . %c \n\n", piece_debug_glyph[m->promoted]);
    printf("captured . . . . . . %c \n\n", piece_debug_glyph[m->captured]);
  }
  printf("%s \n", "{move_str}");
}
