#ifndef __BITBOARD_H__
#define __BITBOARD_H__

#include "./meerkat.h"

void bitboard_debug(bitboard_t);
bitboard_t str_bitboard(char*, int);
bitboard_t bitboard_at(square_t);

#endif /* __BITBOARD_H__ */
