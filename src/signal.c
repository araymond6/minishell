/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:18:48 by araymond          #+#    #+#             */
/*   Updated: 2023/11/03 18:27:15 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		minishell(NULL)->sigint = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	(void)signal;
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		kill(0, 0);
		printf("\n");
		rl_on_new_line();
	}
	else if (signal == SIGQUIT)
	{
		kill(0, 0);
		printf("\n");
		rl_on_new_line();
	}
}

void	set_signal_for_heredoc(t_minishell *mini)
{
	mini->sigact.sa_handler = signal_heredoc;
	sigaction(SIGINT, &mini->sigact, NULL);
	sigaction(SIGQUIT, &mini->sigact, NULL);
}

void	set_signal_for_process(t_minishell *mini)
{
	mini->sigact.sa_handler = sigint_handler;
	sigaction(SIGINT, &mini->sigact, NULL);
	sigaction(SIGQUIT, &mini->sigact, NULL);
}
