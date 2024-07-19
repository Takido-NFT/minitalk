/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalbeck <tmalbeck@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:51:46 by tmalbeck          #+#    #+#             */
/*   Updated: 2024/07/18 17:51:46 by tmalbeck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minitalk.h"

void	send_byte(int server_pid, unsigned char byte)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((byte >> i) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(1000);
		i--;
	}
}

void	send_message(int server_pid, char *message)
{
	int	i;

	i = 7;
	while (*message)
	{
		send_byte(server_pid, *message);
		message++;
	}
	while (i >= 0)
	{
		kill(server_pid, SIGUSR1);
		usleep(1000);
		i--;
	}
}

int	main(int argc, char *argv[])
{
	char				*message;
	int					server_pid;

	if (argc != 3)
		return (1);
	server_pid = atoi(argv[1]);
	message = argv[2];
	send_message(server_pid, message);
	return (0);
}
