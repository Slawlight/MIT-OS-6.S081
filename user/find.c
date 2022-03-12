#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char path[1024];

char*
fmtname(char *path)
{

	char *p;

	// Find first character after last slash.
	for(p=path+strlen(path); p >= path && *p != '/'; p--)
		;
	p++;

	return p;
}



void
find(char *path, char *filename)
{
	int fd;
	struct dirent de;
	struct stat st;

	if((fd = open(path, 0)) < 0)
	{
		fprintf(2, "find: cannot open %s\n", path);
	}
	if(fstat(fd, &st) < 0)
	{
		fprintf(2, "find: cannot stat %s\n", path);
	}
	if(st.type == T_FILE)
	{
		if(strcmp(fmtname(path), filename) == 0)
		{
			fprintf(1, "%s\n", path);
		}
	}
	else if(st.type == T_DIR)
	{

		while(read(fd, &de, sizeof(de)) == sizeof(de))
		{

			char *p = path + strlen(path);
			char *temp = p;

			if(de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
			{
				continue;
			}
			*p++ = '/';
			strcpy(p, de.name);
			find(path, filename);
			*temp = '\0';   //递归回溯
		}

	}
	close(fd);   // 没有这一行会出现bug，open会失败，可能是fd不够用了？
	return;
}



int
main(int argc, char *argv[])
{
	if(argc != 3)
	{
		fprintf(2, "find: need two parameters\n");
		exit();
	}
	strcpy(path, argv[1]);
	find(path, argv[2]);
	exit();
}










