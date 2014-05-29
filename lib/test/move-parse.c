#include <stdio.h>
#include <string.h>
#include "../moves.c"

int main(int argc, char** argv) {
  if(argc != 2) {
    fprintf(stderr,"Usage: %s <move>",argv[0]);
    exit(1);
  }
  char* move;
  parse_m_t pmt;
  position_t* p;
  move = argv[1];

  memcpy(p,&initial_position,sizeof(position_t));
  pmt = parse_move(move,p);
}
