//
// get sys info
//

#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "fs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "file.h"
#include "proc.h"
#include "sysinfo.h"



uint64
sys_info(void)
{
	uint64 st;
	if(argaddr(0, &st) < 0)
	{
		return -1;
	}
	
	if(st > MAXVA)
	{
		return -1;
	}
    int free = getfree();
    int num = unusenum();

    struct proc *p = myproc();

    struct sysinfo sysinfo;
    sysinfo.freemem = free;
    sysinfo.nproc = num;
    if(copyout(p->pagetable, st, (char *)&sysinfo, sizeof(sysinfo)) < 0)
      return -1;
  	return 0;

}