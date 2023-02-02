#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{

    int status = getstate();
    const char *status_names[] = {"UNUSED", "USED", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE"};
    printf("Process PID:    %d\n", getpid());
    printf("Memory Used:    %d\n", getmem());
    printf("Proc State:    %s\n", status_names[status]);
    printf("Uptime (ticks):    %d\n", uptime());
    printf("Parent PID:    %d\n", getparentpid());
    printf("Page Tble Addr:    %x\n", getkstack());

    exit(0);
}