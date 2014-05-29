#include <stdlib.h>
#include <stdio.h>
#include "../meerkat.h"

int main() {
  int i;

  printf("%s ", SQUARE_STR(NO_SQUARE));
  for(i=A1; i <= H8; i++) {
    printf("%s ", SQUARE_STR(i));
  }
  printf("\n");
}
