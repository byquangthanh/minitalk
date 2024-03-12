/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:51:45 by sixshooterx       #+#    #+#             */
/*   Updated: 2024/03/12 13:41:20 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	receive_signal(int sig, siginfo_t *info, void *ucontext)
{
	static int	letter;
	static int	i;
	pid_t		client_pid;

	client_pid = info->si_pid;
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
	kill(client_pid, SIGUSR2);
}

/*
@line 50: We want to receive additional information about the signal
		  Thanks to this, we can get the PID of the client, which sent the signal
@line 51: We use receive_signal as the signal handler
@line 52: Intitialize the signal set sa_mask to empty
sa_mask specifies a set of signals that should be blocked during the execution
*/

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
