#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
  char buff[20];

  setvbuf(stdout, buff, _IOLBF, 20);
  printf("H"); 
  sleep(1);
  printf("e"); 
  sleep(1);
  printf("l"); 
  sleep(1);
  printf("l"); 
  sleep(1);
  printf("o"); 
  sleep(1);

  printf("\n");
  return 0;
}
