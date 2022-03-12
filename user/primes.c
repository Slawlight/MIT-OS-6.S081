#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void 
get_primes(int *p)
{
	int prime_pipe[2];
	int prime;
	pipe(prime_pipe);

	if(read(p[0], &prime, sizeof(int)) != 0)
	{
		fprintf(1, "prime %d\n", prime);
	}
	else
	{
		exit();
	}
 
	if(fork() == 0)
	{
		close(p[0]);            // 注意这一行，之前放在37行，会有 bug
		close(prime_pipe[1]);   // 注意这一行，没有就会出现 bug
		get_primes(prime_pipe);
	}
	else
	{
		int temp_num;
		close(prime_pipe[0]); 
		while(read(p[0], &temp_num, sizeof(int)) != 0){
			// writes to its right neighbor
			if(temp_num % prime != 0){
				write(prime_pipe[1], &temp_num, sizeof(int));
			}
		}     
		close(prime_pipe[1]);   
		wait();
	}
	exit();

}


int 
main(int argc, char *argv[])
{

	int p[2];
	pipe(p);
	for(int i = 2; i < 36; i++)
	{
		write(p[1], &i, sizeof(int));
	}
	close(p[1]);
	get_primes(p);
	exit();
}






