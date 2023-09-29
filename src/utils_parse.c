/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:20:31 by araymond          #+#    #+#             */
/*   Updated: 2023/09/29 11:12:49 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_path(t_minishell *mini)
{
	int		i;
	char	*path;

	i = -1;
	path = "PATH=";
	while (mini->envp[++i])
	{
		if (!ft_strncmp(path, mini->envp[i], ft_strlen(path)))
		{
			return (mini->envp[i]);
		}
	}
	return(NULL);
}

// zeroes t_minishell and set envp
void	initialize_mini(t_minishell *mini, char **envp)
{
	ft_bzero(mini, sizeof(t_minishell));
	mini->envp = envp;
	mini->path = get_path(mini);
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
		mini->cmd = NULL;
	}
}

void	clear_mini(t_minishell *mini)
{
	int	i;

	i = 0;
	mini->parse.block_count = 0;
	mini->parse.c = 0;
	mini->parse.end_block = 0;
	mini->parse.start_block = 0;
	mini->parse.sub = 0;
	i = 0;
	if(!mini->cmd)
		return;
	while (mini->cmd[i])
	{
		free(mini->cmd[i]);
		mini->cmd[i] = NULL;
		i++;
	}
	free(mini->cmd);
	mini->cmd = NULL;
}

// clears history, frees mini's uses and exits program with exit_code depending on the error seen or not seen
void	exit_program(t_minishell *mini)
{
	int exit_code;

	exit_code = mini->exit_code;	
	clear_history();
	free_mini(mini);
	exit(exit_code);
}

void	malloc_error(t_minishell *mini)
{
	mini->exit_code = 1;
	write(STDOUT_FILENO, "malloc error\n", 13);
	exit_program(mini);
}
