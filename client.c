/*client*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "./libft/include/libft.h"

int main(int ac, char **av)
{
	pid_t server_pid;

	if (ac == 3 && ft_isnumi(av[1]))
	{
		server_pid = ft_atoi(*(++av));
		ft_printf("%i", server_pid);
		//kill(server_pid, SIGUSR1); //sends signal SIGUSR1 to a server
		kill(server_pid, SIGUSR2); //sends signal SIGUSR2 to a server

	}
}

