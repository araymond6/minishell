/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:15 by araymond          #+#    #+#             */
/*   Updated: 2023/08/23 16:47:46 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	save_path(t_minishell *mini, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if(ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			mini->path_envp = ft_calloc(ft_strlen(envp[i] - 4), sizeof(char));
			mini->path_envp = envp[i] + 5;
		}
		i++;		
	}
}

int main(int argc, char **argv, char **envp)
{
	t_minishell mini;

	initialize_mini(&mini);
	mini.sigact.sa_handler = signal_handler;
	sigaction(SIGINT, &mini.sigact, NULL);
	sigaction(SIGQUIT, &mini.sigact, NULL);
	save_path(&mini, envp);
	read_input(&mini);
	exit_program(&mini);
}
