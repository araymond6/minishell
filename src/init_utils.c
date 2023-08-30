/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:29:56 by araymond          #+#    #+#             */
/*   Updated: 2023/08/29 14:18:06 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// zeroes t_minishell and set envp
void	initialize_mini(t_minishell *mini, char **envp)
{
	ft_bzero(mini, sizeof(t_minishell));
	mini->envp = envp;
	mini->sigact.sa_handler = signal_handler;
	mini->exit_code = 127;
	sigaction(SIGINT, &mini->sigact, NULL);
	sigaction(SIGQUIT, &mini->sigact, NULL);
}

void	free_triple(char ***arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		while (arr[i][j])
		{
			free(arr[i][j]);
			j++;
		}
		free(arr[i]);
		i++;
	}
	free(arr);
}

// will need at some point
void	free_mini(t_minishell *mini)
{
	if (mini->cmd)
	printf("mini is freed\n");
}

// clears history, frees mini's uses and exits program with exit_code depending on the error seen or not seen
void	exit_program(t_minishell *mini)
{
	int exit_code;

	exit_code = 0;
	exit_code = mini->exit_code;
	printf("exit code: %d\n", mini->exit_code);	
	clear_history();
	free_mini(mini);
	exit(exit_code);
}

// checks our minishell's envp for the environment variable.
int	check_env(t_minishell *mini, char *arg)
{
	int	i;

	i = 0;
	while (mini->envp[i])
	{
		if (ft_strncmp(mini->envp[i], ft_strjoin(arg, "="), ft_strlen(arg)) == 0)
			return (SUCCESS);
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
