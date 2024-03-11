/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:51:45 by sixshooterx       #+#    #+#             */
/*   Updated: 2024/03/11 15:10:35 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>
/*
The logic of the server is as follows:
1. We need to get the server's PID
2. Print the server's PID
3. Wait for the message from the client
4. Print the message, must be quick (1sec for 100 chars is too much)

Features:
- The server must be able to handle multiple clients
- Unix signals
- Two signals: SIGUSR1 and SIGUSR2

Functions we need:
- signal()
- getpid()
- pause()
- write()
- usleep()
- kill()
- ft_printf()
*/
void	receive_signal(int sig, siginfo_t *info, void *ucontext)
{
	static int	letter;
	static int	i;

	(void)info;
	(void)ucontext;
	if (sig == SIGUSR1)
		letter |= (1 << i);
	else if (sig == SIGUSR2)
		letter &= ~(1 << i);
	i++;
	if (i == 8)
	{
		write(1, &letter, 1);
		i = 0;
		letter = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Welcome to minitalk! Server's PID: %d\n", getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = receive_signal;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
