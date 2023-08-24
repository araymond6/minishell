/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:29:56 by araymond          #+#    #+#             */
/*   Updated: 2023/08/24 14:47:47 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// zeroes t_minishell and set envp
void	initialize_mini(t_minishell *mini, char **envp)
{
	ft_bzero(mini, sizeof(t_minishell));
	mini->envp = envp;
	mini->sigact.sa_handler = signal_handler;
	sigaction(SIGINT, &mini->sigact, NULL);
	sigaction(SIGQUIT, &mini->sigact, NULL);
}

// will need at some point
void	free_mini(t_minishell *mini)
{
	printf("mini is freed\n");
}

// clears history, frees mini's uses and exits program with EXIT_CODE
void	exit_program(t_minishell *mini)
{
	clear_history();
	free_mini(mini);
	exit(EXIT_CODE);
}

// checks our minishell's envp for the environment variable.
int	check_env(t_minishell *mini, char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mini->envp[i])
	{
		if (ft_strncmp(mini->envp[i], arg, ft_strlen(arg)) == 0)
		{
			j += ft_strlen(arg);
			while (mini->envp[i][j])
			{
				mini->parse.sub++;
				j++;
			}
			return (SUCCESS);
		}
		i++;
	}
	return (ERROR);
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
