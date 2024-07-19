/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalbeck <tmalbeck@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:27:07 by tmalbeck          #+#    #+#             */
/*   Updated: 2024/07/19 14:27:07 by tmalbeck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minitalk.h"

int	g_client_pid = 0;

void	handle_signal(int signal, siginfo_t *siginfo, void *context)
{
	static int				bit_index = 7;
	static unsigned char	octet = 0;

	(void)context;
	g_client_pid = siginfo->si_pid;
	if (signal == SIGUSR1)
		octet |= (0 << bit_index);
	else if (signal == SIGUSR2)
		octet |= (1 << bit_index);
	bit_index--;
	if (bit_index < 0)
	{
		if (octet == 0)
			printf("\n");
		else
			printf("%c", octet);
		kill(g_client_pid, SIGUSR1);
		bit_index = 7;
		octet = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
