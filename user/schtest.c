#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


// This program is used to test the scheduler.
// The test program should fork() multiple children (min 10)
// and the children should do some work (e.g. compute the sum of 1 to 1000000).
// then dislpay an exit message including its priority, and exit()
// "Process 0 started (priority 0x0A)"
// "Process 0 finished (priority 0x0A)"

void do_work(int processNum, int priority){
    int i, j;
    long long int count = 0;

    for(i = 0; i < 100000; i++){
        for(j = 0; j < 100000; j++){
            count+= i * j;
        }
    }
    printf("Process %d finished (priority 0x%x)\n", processNum, priority);
}
int main(int argc, char *argv[])
{
    int pid;
    //int status;
    
    int children[10] = {0x0A, 0x0D, 0x0C, 0x0A, 0x0F, 0x0A, 0x0A, 0x0F, 0x0A, 0x0C};
    // fork 10 children
    for (int i = 0; i < 10; i++) {
        pid = fork();
        
        if (pid < 0)
        {
            printf("Error: fork failed\n");
            exit(1);
        }
        
        // child
        else if (pid == 0) {

            // if(setpri(children[i]) != 0) {
            //     printf("Error: setpri failed\n");
            //     exit(1);
            // }
            setpri(children[i]);
            sleep(5);
            do_work(i, children[i]);

            //printf("Process %d finished (priority %d)\n", i, getpri());
            exit(0);
        }
        else if (pid > 0) {
            // parent
            
            printf("Process %d started (priority 0x%x)\n", i, children[i]);
        }


    }
    // wait for all child processes to finish
    for(int i=0; i < 10; i++) {
        wait(0);
    }

    return 0;
}