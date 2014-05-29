#ifndef __MEERKAT_H__
#define __MEERKAT_H__

/* bitboard debug characters */
#define BITBOARD_DEBUG_MARK	'x'
#define BITBOARD_DEBUG_BLANK	'.'
/* bitboard mask keys */
#define FILE_A	0
#define FILE_B	1
#define FILE_C	2
#define FILE_D	3
#define FILE_E	4
#define FILE_F	5
#define FILE_G	6
#define FILE_H	7
#define RANK_1	8
#define RANK_2	9
#define RANK_3	10
#define RANK_4	11
#define RANK_5	12
#define RANK_6	13
#define RANK_7	14
#define RANK_8	15
/* convert bitboard mask `rank` and `file` keys to a unique square */
#define MASK_KEY_SQUARE(f,r) \
	(f+8*(r-8) >= 0 && f+8*(r-8) < 64? \
		f+8*(r-8) : NO_SQUARE)
/* misc. bitboard masks */
#define NO_MASK	16
#define UNIVERSE 17
#define CENTER	18
#define RIM	19
#define CORNER	20
/* piece type constants */
#define NO_PIECE	0xe	
#define PAWN	0
#define KNIGHT	0x1
#define BISHOP	0x2
#define ROOK	0x3
#define QUEEN	0x4
#define KING	0x5
/* piece color flags */
#define COLOR	0x8
#define WHITE	0
#define BLACK	0x8
/* castle flags */
#define NO_CASTLE	0
#define CASTLE_WHITE_KINGSIDE	0x1
#define CASTLE_WHITE_QUEENSIDE	0x2
#define CASTLE_BLACK_KINGSIDE	0x4
#define CASTLE_BLACK_QUEENSIDE	0x8
#define ALL_CASTLE	0xf
/* parse move error state */
#define PARSE_MOVE_OK	0
#define PARSE_MOVE_SYNTAX	1
#define PARSE_MOVE_AMBIGUOUS	2
#define PARSE_MOVE_ILLEGAL	3
/* initial white pieces */
#define INITIAL_PIECES_W	0xffffull
#define INITIAL_PAWNS_W	0xff00ull
#define INITIAL_KNIGHTS_W	0x42ull
#define INITIAL_BISHOPS_W	0x24ull
#define INITIAL_ROOKS_W	0x81ull
#define INITIAL_QUEEN_W	0x8ull
#define INITIAL_KING_W	0x10ull
/* initial black pieces */
#define INITIAL_PIECES_B	0xffff000000000000ull
#define INITIAL_PAWNS_B	0xff000000000000ull
#define INITIAL_KNIGHTS_B	0x4200000000000000ull
#define INITIAL_BISHOPS_B	0x2400000000000000ull
#define INITIAL_ROOKS_B	0x8100000000000000ull
#define INITIAL_QUEEN_B	0x800000000000000ull
#define INITIAL_KING_B	0x1000000000000000ull
/* chessboard square constants */
#define NO_SQUARE	-1 /* cleverly, 1<<-1 = 0 */
#define A1	0
#define B1	1
#define C1	2
#define D1	3
#define E1	4
#define F1	5
#define G1	6
#define H1	7
#define A2	8
#define B2	9
#define C2	10
#define D2	11
#define E2	12
#define F2	13
#define G2	14
#define H2	15
#define A3	16
#define B3	17
#define C3	18
#define D3	19
#define E3	20
#define F3	21
#define G3	22
#define H3	23
#define A4	24
#define B4	25
#define C4	26
#define D4	27
#define E4	28
#define F4	29
#define G4	30
#define H4	31
#define A5	32
#define B5	33
#define C5	34
#define D5	35
#define E5	36
#define F5	37
#define G5	38
#define H5	39
#define A6	40
#define B6	41
#define C6	42
#define D6	43
#define E6	44
#define F6	45
#define G6	46
#define H6	47
#define A7	48
#define B7	49
#define C7	50
#define D7	51
#define E7	52
#define F7	53
#define G7	54
#define H7	55
#define A8	56
#define B8	57
#define C8	58
#define D8	59
#define E8	60
#define F8	61
#define G8	62
#define H8	63
/* maps a chessboard square to a string */
#define SQUARE_STR(i) \
	(i==NO_SQUARE? "(null)" : square_str[i])
/* maps a string to a chessboard square */
#define STR_SQUARE(s) \
	(str[0] < 'a' || str[0] > 'h' || str[1] < '1' || str[1] > '8'? NO_SQUARE : \
	A1+(square_t)(str[0]-'a')+8*(square_t)(str[1]-'1'))

typedef int mask_key_t; /* alias for bitboard mask keys */
typedef unsigned long long int bitboard_t; /* alias for bitboards */
typedef char* FEN_t; /* alias for FEN strings */
typedef short castle_t; /* a castle state */
typedef short square_t; /* represents a square on a chessboard */
typedef short piece_t; /* piece info */
typedef short color_t; /* piece color info */
typedef struct {
  square_t src, /* origin of the moving piece */
	dest, /* destination of the moving piece */
	old_ep, /* en passant square before the move is made */
	new_ep; /* en passant square after the move is made */
  int via_ep; /* is it en passant? */
  piece_t moving, /* the moving piece */
	promoted, /* the piece to promote to, if any */
	captured; /* the captured piece, if any */
  castle_t castle; /* the castle state changed, if any */
} move_t; /* a chess move */

typedef int parse_m_err_t; /* A parse move error state */
typedef union {
  move_t* move; /* A parsed move */
  parse_m_err_t err; /* An error state */
} parse_m_t; /* a structure returned from parse_move */
struct pos { /* a piece configuration */
  bitboard_t pieces; /* all pieces */
  bitboard_t piece[6/*7*/]; /* piece bitboards indexed by piece type PAWN..,KING */
}
empty_pos= /* a position with no pieces on it */
	{0,{0,0,0,0,0,0}},
initial_white= /* the initial pos for white */
	{INITIAL_PIECES_W,
	{INITIAL_PAWNS_W,
	 INITIAL_KNIGHTS_W,
	 INITIAL_BISHOPS_W,
	 INITIAL_ROOKS_W,
	 INITIAL_QUEEN_W,
	 INITIAL_KING_W	
	}},
initial_black= /* the initial pos for black */
	{INITIAL_PIECES_B,
	{INITIAL_PAWNS_B,
	 INITIAL_KNIGHTS_B,
	 INITIAL_BISHOPS_B,
	 INITIAL_ROOKS_B,
	 INITIAL_QUEEN_B,
	 INITIAL_KING_B	
	}};
typedef struct pos pos_t; /* alias for piece configuration */
struct position { /* a full chessboard game state */
  pos_t* white; /* white pieces */
  pos_t* black; /* black pieces */
  castle_t castle; /* castling rights */
  square_t enpassant; /* en passant square; if any */
  color_t active_p; /* whose turn? */
  int half_move, /* half-move counter */
	full_move; /* full-move counter */
}
empty_position= /* an empty-initial chessboard */
	{&empty_pos,&empty_pos,0,-1,WHITE,0,1},
initial_position= /* an initial chessboard */
	{&initial_white,&initial_black,ALL_CASTLE,-1,WHITE,0,1};
typedef struct position position_t; /* alias for chess board game state */
const bitboard_t BITBOARD_MASK[] = { /* a table of bitboard masks indexed by a `mask_key_t` */
  0x0101010101010101ull,0x0202020202020202ull,
  0x0404040404040404ull,0x0808080808080808ull,
  0x1010101010101010ull,0x2020202020202020ull,
  0x4040404040404040ull,0x8080808080808080ull,
  0xffull,0xff00ull,
  0xff0000ull,0xff000000ull,
  0xff00000000ull,0xff0000000000ull,
  0xff000000000000ull,0xff00000000000000ull,
  0,0xffffffffffffffffull,
  0x0000001818000000ull,0xff818181818181ffull,
  0x8100000000000081ull
};
const char piece_debug_glyph[] = { /* piece glyphs indexed by a `piece_t` */
  'P','N','B','R','Q','K',' ',
  ' ','p','n','b','r','q','k','.'
};
char* square_str[] = { /* piece square names indexed by a `square_t` */
  "a1","b1","c1","d1","e1","f1","g1","h1",
  "a2","b2","c2","d2","e2","f2","g2","h2",
  "a3","b3","c3","d3","e3","f3","g3","h3",
  "a4","b4","c4","d4","e4","f4","g4","h4",
  "a5","b5","c5","d5","e5","f5","g5","h5",
  "a6","b6","c6","d6","e6","f6","g6","h6",
  "a7","b7","c7","d7","e7","f7","g7","h7",
  "a8","b8","c8","d8","e8","f8","g8","h8"
};

#endif /* __MEERKAT_H__ */
