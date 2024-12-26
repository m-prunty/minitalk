

/*server*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./libft/include/libft.h"
/*
void signal_handler(int signum) 
{
  printf("Received SIGINT!\n", signum);
  exit(0);
  }
  */
void	signal_handler(int signum, siginfo_t *info, void *ucontext)
{
	printf("signo:%i, code:%i, pid:%d, si_uid:%d, addr_ptr:%p, status:%i\n "
		,info->si_signo  /* Signal number */
		,info->si_code   /* Signal code */
		,info->si_pid	/* Sending process ID */
		,info->si_uid	/* Real user ID of sending process */
		,info->si_addr   /* Memory location which caused fault */
		,info->si_status /* Exit value or signal */
			//info->si_value
		  );
	if (signum == SIGUSR1) //if the signal is equal to SIGUSR1 then he prints "Hello World"
		printf("Hello World");
	else if (signum == SIGUSR2)
		printf (" The random number is: %d", rand());
	(void )ucontext;
}

int main()
{
	pid_t	pid;
	struct sigaction	action;

	//sigemptyset(&action.sa_mask);
	pid = getpid();
	ft_printf("The process ID is: %i\n", pid);
	action.sa_sigaction = signal_handler;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	printf("Entering pause...\n");
	pause();
	printf("Exiting pause.\n");
	return (0);
}
