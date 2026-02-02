/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:10:58 by cycolonn          #+#    #+#             */
/*   Updated: 2026/01/28 12:18:29 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

volatile sig_atomic_t	g_receipt;

static long	ft_client_pid(const char *av)
{
	return (ft_atoi(av));
}

static void	ft_signal_handler(int signum, siginfo_t *server, void *context)
{
	(void)context;
	(void)server;
	if (signum == SIGUSR2)
		g_receipt = 1;
	if (signum == SIGUSR1)
		exit(EXIT_FAILURE);
}

static void	ft_aknowledgement(void)
{
	int	timer;

	timer = 0;
	while (!g_receipt)
	{
		usleep(10);
		timer++;
		if (timer == 70000)
		{
			ft_putstr("SERVER CONNECTION LOST...");
			exit(EXIT_FAILURE);
		}
	}
}

static void	ft_send_char(char c, int client_pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_receipt = 0;
		if (c & (1 << i))
			kill(client_pid, SIGUSR2);
		else
			kill(client_pid, SIGUSR1);
		ft_aknowledgement();
		i++;
	}
}

int	main(int ac, char **av)
{
	int					client_pid;
	struct sigaction	sig_a;

	if (ac != 3)
		return (ft_putstr("WRONG ARGUMENTS\n"), (0));
	client_pid = ft_client_pid(av[1]);
	if (client_pid <= 0)
		return (ft_putstr("WRONG PID\n"), (0));
	sig_a.sa_flags = SA_SIGINFO;
	sig_a.sa_sigaction = ft_signal_handler;
	sigemptyset(&sig_a.sa_mask);
	sigaction(SIGUSR1, &sig_a, NULL);
	sigaction(SIGUSR2, &sig_a, NULL);
	while (*av[2])
	{
		ft_send_char(*av[2], client_pid);
		av[2]++;
	}
	ft_send_char(*av[2], client_pid);
	return (0);
}
