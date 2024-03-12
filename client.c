/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:51:25 by sixshooterx       #+#    #+#             */
/*   Updated: 2024/03/12 14:25:55 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
tracks wether the ack signal was received
volatile: the value of the variable can change at any time,
		  important for signal handling
sig_atomic_t: int type that can be accessed atomically, that means
			  it can be accessed by the signal handler and the main program
			  at the same time
			  ensures that the variable is not accessed while it is being modified
*/
volatile sig_atomic_t	g_ack_received = 0;

/*
handles SIGUSR2 signal, which are sent by the server to acknowledge the
reception of a bit
*/
void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

/*
before sending each bit, g_ack_received is reset to 0
After sending a bit, the client enters a loop, pausing until g_ack_received
is set to 1 (acknowledgment received).
This ensures that the client waits for an acknowledgment after sending
each bit before proceeding
*/

static void	send_bit(int server_pid, char *message)
{
	int	i;
	int	j;

	i = 0;
	while (message[i])
	{
		j = 0;
		while (j < 8)
		{
			g_ack_received = 0;
			if (message[i] & (1 << j))
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			j++;
			while (!g_ack_received)
				pause();
			usleep(100);
		}
		i++;
	}
}

static void	send_signal(int server_pid, char *message)
{
	struct sigaction	sa;

	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR2, &sa, NULL);
	send_bit(server_pid, message);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Usage: ./client [server's PID] [message]\n");
		return (1);
	}
	else
		send_signal(ft_atoi(argv[1]), argv[2]);
	return (0);
}
