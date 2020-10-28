#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main() {
  int f1 = open("ex1.txt", O_RDWR);
  int f2 = open("ex1.memcpy.txt", O_RDWR);
  struct stat st1, st2;
  int ok = fstat(f1, &st1);
  if (ok){
    printf("ERROR!");
    return 1;
  }
  ok = fstat(f2, &st2);
  if (ok){
    printf("ERROR!");
    return 1;
  }
  ftruncate(f2, st1.st_size);
  char* fm1 = mmap(NULL, st1.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, f1, 0);
  char* fm2 = mmap(NULL, st2.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, f2, 0);
  memcpy(fm2, fm1, st1.st_size);
  msync(fm1, st1.st_size, MS_SYNC);
  msync(fm2, st1.st_size, MS_SYNC);
  munmap(fm1, st1.st_size);
  munmap(fm2, st1.st_size);
  close(f1);
  close(f2);
  return 0;
}
