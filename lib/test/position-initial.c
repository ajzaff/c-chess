#include <string.h>
#include "../position.c"

int main() {
  position_t* p;

  p=copy_position(&initial_position);
  printf("debug initial white: \n");
  pos_debug(p->white);
  printf("debug initial black: \n");
  pos_debug(p->black);
  printf("debug initial: \n");
  position_debug(p,1);
  printf("debug finished \n");
  free_position(p);
}
