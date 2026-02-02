/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:11:50 by cycolonn          #+#    #+#             */
/*   Updated: 2026/01/28 12:11:52 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

t_sent		g_char;

static void	ft_pid_display(void)
{
	write(1, "SERVER PID : ", 13);
	ft_putnbr(getpid());
	write(1, "\n", 1);
}

static void	ft_init_client(t_sent *client, int info_pid)
{
	if (client->pid != info_pid)
	{
		client->cur_char = 0;
		client->count_bits = 0;
		client->pid = info_pid;
	}
}

static void	ft_signal_handler(int signum, siginfo_t *client, void *context)
{
	(void)context;
	ft_init_client(&g_char, client->si_pid);
	if (signum == SIGUSR2)
		g_char.cur_char |= (1 << g_char.count_bits);
	g_char.count_bits++;
	if (g_char.count_bits == 8)
	{
		write(1, &g_char.cur_char, 1);
		if (g_char.cur_char == '\0')
			write(1, "\n", 1);
		g_char.count_bits = 0;
		g_char.cur_char = 0;
	}
	kill(client->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sig_a;

	sig_a.sa_flags = SA_SIGINFO;
	sig_a.sa_sigaction = ft_signal_handler;
	sigemptyset(&sig_a.sa_mask);
	sigaction(SIGUSR1, &sig_a, NULL);
	sigaction(SIGUSR2, &sig_a, NULL);
	ft_pid_display();
	while (1)
	{
		pause();
	}
}
