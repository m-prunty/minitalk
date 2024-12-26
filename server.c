/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 17:06:36 by mprunty           #+#    #+#             */
/*   Updated: 2024/12/26 19:56:34 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk.h"

void	signal_handler(int signum, siginfo_t *info, void *ucontext)
{
	static unsigned char	c = 0;
	static int				bits= 0;
	
	//printf("c:%i, bits:%i\n", c, bits);

	if (bits == 8)
	{
		//write(1, "\n", 1);
		write(1, &c, 1);
		//write(1, "\n", 1);
		c = 0;
		bits = 0;
	}
	c = c | ((signum == SIGUSR1) << bits);
	bits++;
	kill(info->si_pid, SIGUSR2);

/*
	printf("signo:%i, code:%i, pid:%d, si_uid:%d, addr_ptr:%p, status:%i\n "
		,info->si_signo  # Signal number 
		,info->si_code   # Signal code 
		,info->si_pid	# Sending process ID 
		,info->si_uid	# Real user ID of sending process 
		,info->si_addr   # Memory location which caused fault 
		,info->si_status # Exit value or signal 
			//info->si_value
		  );
*/
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
	ft_printf("Entering pause...\n");
	while (pause());
	ft_printf("Exiting pause.\n");
	return (0);
}
