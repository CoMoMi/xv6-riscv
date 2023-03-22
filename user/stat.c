#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{

    int status = getstate();
    int priority = getpri();
    const char *status_names[] = {"UNUSED", "USED", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE"};
    const char *priority_states[] = {"0x0A", "0x0B", "0x0C", "0x0D", "0x0F"};
    const char *priority_name;

    if (priority == 15)
        priority_name = priority_states[4];
    else
        priority_name = priority_states[priority - 10];

    printf("Process PID:    %d\n", getpid());
    printf("Priority:    %s\n", priority_name);
    printf("Memory Used:    %d\n", getmem());
    printf("Proc State:    %s\n", status_names[status]);
    printf("Uptime (ticks):    %d\n", uptime());
    printf("Parent PID:    %d\n", getparentpid());
    printf("Page Tble Addr:    %x\n", getkstack());

    exit(0);
}