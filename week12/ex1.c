#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 20

int main(){
	FILE *random = open("/dev/random", O_RDONLY);
	if (random < 0){
	    return -1;
	}
    char array[SIZE + 1];
    int res = read(random, array, SIZE);
    if (res < 0){
        close(random);
        return -1;
    }
	printf("\n");
	close(random);
	return 0;
}
