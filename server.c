/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 17:06:36 by mprunty           #+#    #+#             */
/*   Updated: 2024/12/26 23:32:39 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk.h"

void	signal_handler(int signum, siginfo_t *info, void *ucontext)
{
	static unsigned char	c = 0;
	static int				bits = 0;

	if (bits == 8)
	{
		write(1, &c, 1);
		c = 0;
		bits = 0;
	}
	c = c | ((signum == SIGUSR1) << bits);
	bits++;
	kill(info->si_pid, SIGUSR2);
	(void )ucontext;
}

int	main(void)
{
	struct sigaction	action;
	pid_t				pid;

	pid = getpid();
	ft_printf("The process ID is: %i\n", pid);
	action.sa_sigaction = signal_handler;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	ft_printf("Entering pause...\n");
	while (pause())
		;
	ft_printf("Exiting pause.\n");
	return (0);
}
