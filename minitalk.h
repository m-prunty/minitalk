/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprunty <mprunty@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:33:11 by mprunty           #+#    #+#             */
/*   Updated: 2024/12/26 23:37:34 by mprunty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include "./libft/include/libft.h"
# include <unistd.h>

//client.c
void	signal_response(int signum);
void	send_char(pid_t server_pid, char c);

//server.c	
void	signal_handler(int signum, siginfo_t *info, void *ucontext);

#endif
