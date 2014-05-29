#include "../bitboard.c"

int main(int argc, char** argv) {
  if(argc!=3) {
    printf("Usage: %s <value> <base>\n", argv[0]);
    exit(1);
  }
  bitboard_t b;
  int base;

  base = atoi(argv[2]);
  b = strtoull(argv[1],0,base);

  // debug the bitboard
  bitboard_debug(b);
}
