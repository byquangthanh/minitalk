/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:51:25 by sixshooterx       #+#    #+#             */
/*   Updated: 2024/03/11 15:10:39 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
1. Receive the server's PID
2. Client takes two parameters: the server's PID and the message
3. Client must send the message to the server
*/

void	send_signal(int server_pid, char *message)
{
	int	i;
	int	j;

	i = 0;
	while (message[i])
	{
		j = 0;
		while (j < 8)
		{
			if (message[i] & (1 << j))
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			j++;
			usleep(100);
		}
		i++;
	}
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
