#include <stdlib.h>
#include <stdio.h>
#include "../FEN.c"

int main(int argc, char** argv) {
  if(argc!=2) {
    printf("Usage: %s <fen> \n",argv[0]);
    exit(1);
  }
  FEN_t f = argv[1];
  position_t* p;

  p = FEN_position(f);
  if(p!=NULL) {
    position_debug(p,1);
    free_position(p);
  }
}
