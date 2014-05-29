#ifndef __MOVES_H__
#define __MOVES_H__

#include "./meerkat.h"

parse_m_t parse_move(char*, position_t*);
piece_t parse_piece(char*,int);
piece_t parse_promo(char*,int);
mask_key_t parse_file(char*,int);
mask_key_t parse_rank(char*,int);
void move_make(move_t*, position_t*);
void move_unmake(move_t*, position_t*);
void move_debug(move_t*,int);
void move_str(move_t*,char*);

#endif /* __MOVES_H__ */
