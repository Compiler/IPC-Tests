#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int job2_permute_10(int len){
    if(len <= 0){
        printf("\n");
        return 0;
    }
    printf("1");
    job2_permute_10(len-1);
    printf("0");
    job2_permute_10(len-1);
    printf("*");
    return 0;
}
int job1_calc_fib(int n){
    if(n <= 2) return n;
    int a = job1_calc_fib(n - 1);
    int b = job1_calc_fib(n - 2);
    printf("%d\n", a + b);
    return a + b;
}
int main(void){
    pid_t pid;
    int rv;
    int sum = 0;
    const int JOBS = 2;
    int(*jobs[JOBS])(int);
    jobs[0] = job1_calc_fib;
    jobs[1] = job2_permute_10;

    for(int i = 0; i < JOBS; i++){
        switch(pid = fork()) {
            case -1:
                perror("fork failed"); /* something went wrong */
                exit(1); /* parent exits */
            case 0:
                printf(" CHILD: PID is %d\n", getpid());
                printf(" CHILD: PPID is %d\n", getppid());
                printf(" CHILD: running child\n");
                rv = jobs[i](5);
                printf(" CHILD: Done!\n");
                exit(rv);
            default:
                printf("PARENT: PID is %d\n", getpid());
                printf("PARENT: Child PID is %d\n", pid);
                printf("PARENT: I'm now waiting for my child to exit()...\n");
                wait(&rv);
                printf("PARENT: My child's exit status is: %d\n", WEXITSTATUS(rv));
                printf("PARENT: Done!\n");
        }
    }
    printf("Final: %d\n", sum);
    return 0;
}