#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[])
{
	int parent_fdp[2], child_fd[2];
	char buf1[512], buf2[512];
	pipe(parent_fdp);
	pipe(child_fd);

	if(fork() == 0){
		int pid_num = getpid();

		// read message 
		close(parent_fdp[1]);
		read(parent_fdp[0], buf1, sizeof(buf1));
		fprintf(1, "%d: received %s\n", pid_num, buf1);

		// write message to pipe in child process
		char *c_msg = "pong";
		close(child_fd[0]);
		write(child_fd[1], c_msg, strlen(c_msg));
		close(child_fd[1]);
	}
	else{

		// 这里加上sleep(10),子进程read会等待，
		// 当管道写端未关闭时，read会阻塞
		char *p_msg = "ping";
		int pid_num = getpid();
		close(parent_fdp[0]);
		write(parent_fdp[1], p_msg, strlen(p_msg));
		close(parent_fdp[1]);

		// read message
		close(child_fd[1]);
		read(child_fd[0], buf2, sizeof(buf2));
		fprintf(1, "%d: received %s\n", pid_num, buf2);


	}
	exit();
}