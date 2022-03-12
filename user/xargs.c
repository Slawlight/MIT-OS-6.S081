#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	char* args[MAXARG];
	char buf[512];

	for (int i = 1; i < argc; i++)
	{
		args[i-1] = argv[i];
	}
	int argindex = argc - 1;
	int index = 0;
	while(read(0, &buf[index], 1) != 0) 
	{
		if(buf[index] == '\n')
		{
			buf[index] = 0;

			args[argindex] = buf;

			if(fork() == 0)
			{
				exec(argv[1], args);
				exit();
			}
			else
			{
				wait();
				index = 0;
				argindex = argc - 1;
			}
		}
		else
		{
			index++;
		}
		
	}

	
	exit();
}