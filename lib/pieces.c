#include "./pieces.h"

/*
 * Converts the SAM glyph to a fully qualified piece, if valid
 */

piece_t glyph_piece(char g) {
  piece_t p;

  for(p=PAWN; p<=KING; p++) { // match white glyphs
    if(g == piece_debug_glyph[WHITE|p]) {
      return WHITE|p;
    }
  }
  for(p=PAWN; p<=KING; p++) { // match black glyphs
    if(g == piece_debug_glyph[BLACK|p]) {
      return BLACK|p;
    }
  }
  return NO_PIECE;
}
