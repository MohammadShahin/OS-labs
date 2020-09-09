#include <sys/types.h>
#include <stdio.h>

int main() {
    int n = -110;
    pid_t pid;
    pid = fork();
    if (pid == -1){
      return 1;
    }
    if (pid == 0){
    printf("Hello from child [%d - %d]\n", pid, n);
      return 0;
    }
    printf("Hello from parent [%d - %d]\n", pid, n);
    return 0;
}
