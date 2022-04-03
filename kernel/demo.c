#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"

void demo1()
{
	printf("Res:%d\n", sum_to(5));
}

void demo2()
{
	printf("Res:%d\n", sum_then_double(5));
}


uint64 sys_demo(void)
{
	demo2();
	return 0;
}