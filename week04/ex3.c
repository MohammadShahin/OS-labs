#include <stdio.h>
void main() {
  char str[256];
  while(1) {
    fgets(str, 256, stdin);
    system(str);
  }
}
