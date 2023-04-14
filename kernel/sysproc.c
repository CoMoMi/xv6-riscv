#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//-----------------------------------------
//project 2a add system calls

//get the memory size of calling process
uint64
sys_getmem(void){
  uint64 memsize;
  memsize = myproc()->sz;
  return memsize;
}

// returns the current state
uint64
sys_getstate(void){
  return myproc()->state;
}

// returns the parents pid
uint64
sys_getparentpid(void){
  return myproc()->parent->pid;
}

//get the address of the stack
uint64
sys_getkstack(void){
  uint64 addr;
  addr = myproc()->kstack;
  return addr;
}

//-----------------------------------------
//project 5a add system calls

//set the priority of the calling process
uint64
sys_setpri(void){
  int n;

  argint(0, &n);          //get the priority from the argument
 

  if(n != 0x0A && n != 0x0B && n != 0x0C && n != 0x0D && n != 0x0F){   //check if the priority is valid
    return -1;
  }
  
  //acquire(&p->lock);
  myproc()->priority = n;
  //release(&p->lock);
  return 0;
}

//get the priority of the calling process
uint64
sys_getpri(void){
  return myproc()->priority;
}

