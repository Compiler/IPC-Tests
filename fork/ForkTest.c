#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(void){
    pid_t pid;
    int rv;
    int sum = 0;
    const int CHILD_PROC = 5;
    int arr[CHILD_PROC];
    for(int i = 0; i < CHILD_PROC; i++){
        switch(pid = fork()) {
        case -1:
        perror("fork failed"); /* something went wrong */
        exit(1); /* parent exits */
        case 0:
        printf(" CHILD: PID is %d\n", getpid());
        printf(" CHILD: PPID is %d\n", getppid());
        printf(" CHILD: Enter exit status...\n");
        scanf(" %d", &rv);
        printf(" CHILD: Done!\n");
        exit(rv);
        default:
        printf("PARENT: PID is %d\n", getpid());
        printf("PARENT: Child PID is %d\n", pid);
        printf("PARENT: I'm now waiting for my child to exit()...\n");
        wait(&rv);
        arr[i] = WEXITSTATUS(rv);
        printf("PARENT: My child's exit status is: %d\n", WEXITSTATUS(rv));
        printf("PARENT: Done!\n");
        }
    }
    printf("Final: %d\n", sum);
    return 0;
}