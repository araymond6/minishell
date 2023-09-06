/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:29:56 by araymond          #+#    #+#             */
/*   Updated: 2023/09/06 14:04:27 by araymond         ###   ########.fr       */
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

// will need at some point
void	free_mini(t_minishell *mini)
{
	int	i;

	i = -1;
	if (mini->cmd)
	{
		while (mini->cmd[++i])
			free(mini->cmd[i]);
		free(mini->cmd);
	}
	printf("mini is freed!\n");
}

// clears history, frees mini's uses and exits program with exit_code depending on the error seen or not seen
void	exit_program(t_minishell *mini)
{
	int exit_code;

	exit_code = mini->exit_code;
	printf("exit code: %d\n", mini->exit_code);	
	clear_history();
	free_mini(mini);
	exit(exit_code);
}

static char	*while_env(t_minishell *mini, int *i, int *k, char *new)
{
	while (mini->envp[*i])
	{
		if (ft_strncmp(mini->envp[*i], new, ft_strlen(new)) == 0)
		{
			free(new);
			new = ft_calloc((ft_strlen(mini->envp[*i]) + 1), sizeof(char));
			if (!new)
				return (NULL);
			while (mini->envp[*i][*k])
			{
				new[*k] = mini->envp[*i][*k];
				(*k)++;
			}
			return (new);
		}
		(*i)++;
	}
	return (NULL);
}

// checks our minishell's envp for the env variable, returns char *;
char	*check_env(t_minishell *mini, char *arg)
{
	int		i;
	int		k;
	char	*new;
	
	i = 0;
	k = 0;
	if (!arg || arg[0] == '\0')
		return (1);
	new = ft_strjoin(arg, "=");
	if (!new)
	return (NULL);
	new = while_env(mini, &i, &k, new);
	if (new)
		return (new);
	return (NULL);
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
