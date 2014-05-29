#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include "./FEN.h"
#include "./moves.h"
#include "./position.c"
#include "./pieces.c"

position_t* FEN_position(FEN_t fen) {
  position_t* pos;
  mask_key_t file,rank;

  /* parse board configuration */
  file = FILE_A;
  rank = RANK_8;
  pos = copy_position(&empty_position);
  do {
    //square_t sq = MASK_KEY_SQUARE(file,rank);
    //printf("%s ", SQUARE_STR(sq));
    consume_board_conf_char(&fen,&file,&rank,pos);
  } while(rank >= RANK_1);
  consume_space(&fen,pos);

  /* parse active player */
  consume_active_p(&fen,pos);
  consume_space(&fen,pos);

  /* parse castle rights */
  consume_castle_rights(&fen,pos);
  consume_space(&fen,pos);

  /* parse en passant square */
  consume_en_passant(&fen,pos);
  consume_space(&fen,pos);

  /* parse half-move counter */
  consume_integer(&fen,pos);
  consume_space(&fen,pos);

  /* parse full-moves */
  consume_integer(&fen,pos);

  return pos;
}

void consume_board_conf_char(FEN_t* fen, mask_key_t* file, mask_key_t* rank, position_t* pos) {
  square_t sq;
  piece_t p;
  int d;

  d=0;
  p=glyph_piece(**fen);
  sq=MASK_KEY_SQUARE(*file,*rank);
  if(p != NO_PIECE) { // piece
    if((p & COLOR) == BLACK) { // black piece
      pos->black->piece[p & ~COLOR] |= 1ull << sq;
      pos->black->pieces |= 1ull << sq;
    }
    else { // white piece
      pos->white->piece[p & ~COLOR] |= 1ull << sq;
      pos->white->pieces |= 1ull << sq;
    }
    (*file)++; // advance to the next file
    (*fen)++; // advance the string pointer
  }
  else if(isdigit(**fen)) { // blank squares,0,9
    d = consume_integer(fen,pos); // read an integer
    if(d == 0 || d == 9) { // error
      FEN_position_error(pos,"error: bad digit in board configuration: `%d`: at %s",d,SQUARE_STR(sq));
    }
    if(*file+d > 8) { // error
      FEN_position_error(pos,"error: rank %d is too long: near `%d`: at %s",*rank-7,d,SQUARE_STR(sq));
    }
    *file += d; // advance to the next
  }
  else { // error
    FEN_position_error(pos,"error: unexpected character in board configuration: `%c`: at %s",**fen,SQUARE_STR(sq));
  }
  if(*file > FILE_H) { // at end, wrap around
    if(*rank > RANK_1) { // no rank 1 seperator
      if(**fen == '/') { // required rank seperator
        (*fen)++; // advance the string pointer
      }
      else { // error
        FEN_position_error(pos,"error: missing `/` to end rank %d: found `%c`",*rank-7,**fen);
      }
    }
    *file = FILE_A;
    (*rank)--;
  }
}

void consume_space(FEN_t* fen,position_t* pos) {
  if(**fen != ' ') {
    FEN_position_error(pos,"error: expected ` `: found `%c`",**fen);
  }
  (*fen)++;
}

void consume_active_p(FEN_t* fen, position_t* pos) {
  if(**fen == 'w') {
    pos->active_p = WHITE;
  }
  else if(**fen == 'b') {
    pos->active_p = BLACK;
  }
  else {
    FEN_position_error(pos,"error: unexpected active player: `%c`",**fen);
  }
  (*fen)++;
}

void consume_castle_rights(FEN_t* fen, position_t* pos) {
  if(**fen == '-') {
    pos->castle = NO_CASTLE;
    (*fen)++;
  }
  else {
    if(**fen == 'K') {
      pos->castle |= CASTLE_WHITE_KINGSIDE;
      (*fen)++;
    }
    if(**fen == 'Q') {
      pos->castle |= CASTLE_WHITE_QUEENSIDE;
      (*fen)++;
    }
    if(**fen == 'k') {
      pos->castle |= CASTLE_BLACK_KINGSIDE;
      (*fen)++;
    }
    if(**fen == 'q') {
      pos->castle |= CASTLE_BLACK_QUEENSIDE;
      (*fen)++;
    }
    if(pos->castle == NO_CASTLE) { // error
      FEN_position_error(pos,"error: unexpected castle flag: `%c`",**fen);
    }
  }
}

void consume_en_passant(FEN_t* fen, position_t* pos) {
  square_t sq;
  char str[3];

  if(**fen == '-') {
    pos->enpassant = NO_SQUARE;
    (*fen)++;
  }
  else {
    str[0] = *((*fen)++);
    str[1] = *((*fen)++);
    str[2] = '\0';
    sq = STR_SQUARE(str);
    if(sq == NO_SQUARE) { // error
      FEN_position_error(pos,"error: invalid en passant square: %s",str);
    }
    pos->enpassant = sq;
  }
}

int consume_integer(FEN_t* fen,position_t* pos) {
  int d;

  if(!isdigit(**fen)) {
    FEN_position_error(pos,"error: unexpected integer value `%d`",**fen);
  }
  d = atoi(*fen);
  while(isdigit(**fen)) (*fen)++; // fast forward the pointer
  return d;
}

void FEN_position_error(position_t* pos,const char* format,...) {
  va_list vl;
  va_start(vl,format);
  vprintf(format,vl);
  printf("\n");
  va_end(vl);
  free_position(pos);
  exit(1);
}

int FEN_valid(FEN_t f) {
  position_t* p;
  int valid;

  p = FEN_position(f);
  if(valid=p!=NULL) {
    free_position(p);
  }
  return valid;
}
