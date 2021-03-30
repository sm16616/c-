//Pack 3 components, each 0..255, into a colour.
#include <stdio.h>

int main() {
  setbuf(stdout, NULL);
  int c = (r << 24) | (g << 16) | (b << 8) | o;;
  int r = red;
  int g = green;
  int b = blue;
  int o = opacity;
  printf("%d\n", c);

  return 0;
}

int pack(int r, int g, int b, int o) {
  int c = (r << 24) | (g << 16) | (b << 8) | o;
   return c;
}
