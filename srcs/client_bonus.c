/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalbeck <tmalbeck@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:26:37 by tmalbeck          #+#    #+#             */
/*   Updated: 2024/07/19 14:26:37 by tmalbeck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minitalk.h"

int	g_confirmation_received = 0;

void	confirmation_handler(int signal)
{
	if (signal == SIGUSR1)
		g_confirmation_received = 1;
}

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
		usleep(400);
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
		while (!g_confirmation_received)
			usleep(400);
		g_confirmation_received = 0;
		message++;
	}
	while (i >= 0)
	{
		kill(server_pid, SIGUSR1);
		usleep(400);
		i--;
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	char				*message;
	int					server_pid;

	if (argc != 3)
		return (1);
	server_pid = atoi(argv[1]);
	message = argv[2];
	sa.sa_handler = confirmation_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	send_message(server_pid, message);
	while (!g_confirmation_received)
		pause();
	printf("Server succesfully received message.\n");
	return (0);
}
