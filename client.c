/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 17:02:48 by mprunty           #+#    #+#             */
/*   Updated: 2024/12/26 23:33:01 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk.h"

int	g_sigrecived = 0;

/**
 * @brief Sets g_sigrecived to 1 if signum is SIGUSR2
 *
 * @param signum 
 */
void	signal_response(int signum)
{
	if (signum == SIGUSR2)
		g_sigrecived = 1;
}

/**
 * @brief Sends a char to the server, 
 * c>>i shifts the bits right by i, 
 * if 1 sends kill signal with SIGUSR1, 
 * else sends kill signal with SIGUSR2
 * it then waits for a response from the server
 *
 * @param server_pid 
 * @param c 
 */
void	send_char(pid_t server_pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		i++;
		(usleep(500));
		while (!g_sigrecived)
			;
		g_sigrecived = 0;
	}
}

int	main(int ac, char **av)
{
	pid_t	server_pid;
	char	*str;

	if (ac == 3 && ft_isnumi(av[1]))
	{
		str = ft_strdup(av[2]);
		server_pid = ft_atoi(*(++av));
		signal(SIGUSR2, signal_response);
		while (*str)
		{
			send_char(server_pid, *str++);
		}
	}
	else
	{
		ft_printf("Usage: ./client [server_pid] [message]\n");
	}
}
