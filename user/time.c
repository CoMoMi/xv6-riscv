#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    //Accepts arguments from the command line interface. Add the 
    //necessary error checking with appropriate error messages
    if (argc < 2){
        printf("Usage: time <command>\n");
        exit(1);
    }

    int status;

    //1.get the current time using uptime
    // get current time
    int currentTime = uptime();

    //2.use the fork() system call and then wait for the child process to terminate
    int pid = fork();
    if (pid < 0){
        printf("Fork not sucessful\n");
        exit(1);
    }
    else if(pid == 0){
        //child process
        if(exec(argv[1], argv + 1) < 0){
            printf("Execution error\n");
            exit(0);
        }
    }
    else{
        //3.When the wait() system call returns to the parent
        //  process get the current time again and calculate the difference

        //wait till child finish with status code
        wait(&status);

        //parent process
        int newTime = uptime();
        printf("\nReal-time in ticks: %d\n", newTime - currentTime);
    }
    
    exit(0);
}