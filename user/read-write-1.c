// CS 370
// A simple readers/writers program using a one-word shared memory.

#include <sys/types.h> // for pid_t
#include <unistd.h> // for fork
#include <stdio.h> // for printf
#include <sys/mman.h> // for mmap
#include <sys/wait.h> // for waitpid
#include <stdlib.h> // for exit
#include <stdbool.h> // for bool type
#define BUF_SIZE 5 // logical size of buffer
#define SHARED_MEM_SIZE (BUF_SIZE+2)*sizeof(int) // size of shared memory
#define run_length 10 // number of iterations in test run

int main (void) {
    pid_t pid; // variable to record process id of child
    caddr_t shared_memory; // shared memory base address
    int *in; // pointer to logical 'in' address for writer
    int *out; // pointer to logical 'out' address for reader
    int *buffer; // logical base address for buffer
    int *lock; // pointer to shared memory location for spinlock
    int i_child, j_child; // index variables
    int value; // value read by child
    bool locked; // flag to indicate whether spinlock is active

    // set up shared memory segment
    shared_memory = mmap(0, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (shared_memory == (caddr_t) -1) {
        perror("error in mmap while allocating shared memory\n");
        exit(1);
    }

    // Shared memory segment will be organized as follows:
    // 0                                                   n-1 n  n+1
    // ---------------------------------------------------------------
    // |                                                       |  |  |
    // ---------------------------------------------------------------
    // ^                                                       ^  ^
    // buffer                                                  in out
    buffer = (int*) shared_memory; // logical buffer starts at shared segment
    in = (int*) shared_memory + BUF_SIZE*sizeof(int);
    out = (int*) shared_memory + (BUF_SIZE+1)*sizeof(int);
    lock = (int*) shared_memory + (BUF_SIZE+2)*sizeof(int);
    *in = *out = *lock = -1; // initial starting points

    // check for error in spawning child process
    if (-1 == (pid = fork())) {
        perror("error in fork");
        exit(1);
    }

    if (0 == pid) {
        // processing for child == reader
        printf("\033[0;31mThe child process begins.\033[0m\n");
        for (i_child = 0; i_child < run_length; i_child++) {
            locked = true;
            while (locked) { // spinlock waiting for lock to be released
                if (*lock >= 0) {
                    locked = false;
                }
            }
            value = buffer[*out];
            *out = (*out + 1) % BUF_SIZE;
            printf("\033[0;31mReader's report: item %2d == %2d\033[0m\n", i_child, value);
            if (i_child == run_length - 1) {
                *lock = -1; // release the lock
            }
        }
        printf("\033[0;31mReader done.\033[0m\n");
    } else {
        // processing for parent == writer
        printf("The writer process begins.\n");
        for (j_child = 0; j_child < run_length; j_child++) {
            locked = true;
            while (locked) { // spinlock waiting for lock to be released
			}
		}
	}

	exit(0);
}

