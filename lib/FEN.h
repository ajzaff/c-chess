#ifndef __FEN_H__
#define __FEN_H__

#include "./meerkat.h"

position_t* FEN_position(FEN_t);
void consume_board_conf_char(FEN_t*,mask_key_t*,mask_key_t*,position_t*);
void consume_space(FEN_t*,position_t*);
void consume_active_p(FEN_t*,position_t*);
void consume_castle_rights(FEN_t*,position_t*);
void consume_en_passant(FEN_t*,position_t*);
int consume_integer(FEN_t*,position_t*);
void FEN_position_error(position_t*,const char*,...);
int FEN_valid(FEN_t);

#endif /* __FEN_H__ */
