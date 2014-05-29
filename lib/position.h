#ifndef __POSITION_H__
#define __POSITION_H__

#include "./meerkat.h"

position_t* copy_position(position_t*);
pos_t* copy_pos(pos_t*);
void free_position(position_t*);
piece_t position_piece(position_t*,square_t);
piece_t pos_piece(pos_t*,square_t);
void position_debug(position_t*,int);
void pos_debug(pos_t*);

#endif /* __POSITION_H__ */
