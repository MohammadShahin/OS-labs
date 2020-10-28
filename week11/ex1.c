#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main() {
  char* text = "This is a nice day";
  size_t textsize = strlen(text); // + \0 null character
  int f = open("ex1.txt", O_RDWR);
  ftruncate(f, textsize);
  struct stat st;
  int ok = fstat(f, &st);
  if (ok){
    printf("ERROR!");
    return 1;
  }
  char* fm = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, f, 0);
  for (size_t i = 0; i < textsize; i++){
    //printf("Writing character %c at %zu\n", text[i], i);
    fm[i] = text[i];
  }
  msync(fm, textsize, MS_SYNC);
  munmap(fm, textsize);
  close(f);
  return 0;
}
