/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:17:22 by araymond          #+#    #+#             */
/*   Updated: 2023/11/07 15:17:48 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_path(t_minishell *mini)
{
	find_path2(mini);
	free(mini->s_cmd->cmd_arg[0]);
	mini->s_cmd->cmd_arg[0] = NULL;
	mini->s_cmd->cmd_arg[0] = \
		ft_calloc(ft_strlen(mini->s_cmd->path) + 1, sizeof(char));
	if (!mini->s_cmd->cmd_arg[0])
		mini->s_cmd->cmd_arg[0] = NULL;
	ft_strlcpy(mini->s_cmd->cmd_arg[0],
		mini->s_cmd->path, ft_strlen(mini->s_cmd->path) + 1);
}

char	*child_path_execve(char *string)
{
	char	*new_path_execve;
	int		i;

	i = 0;
	if (!string)
		return (NULL);
	new_path_execve = ft_calloc(ft_strlen(string) + 1, sizeof(char));
	if (!new_path_execve)
		return (NULL);
	while (string[i])
	{
		new_path_execve[i] = string[i];
		i++;
	}
	return (new_path_execve);
}

void	child_array_execve_loop(char **array, char **new_array_execve)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (array[i])
	{
		new_array_execve[i] = ft_calloc(ft_strlen(array[i]) + 1, sizeof(char));
		if (!new_array_execve[i])
		{
			free_array(new_array_execve);
			new_array_execve = NULL;
			return ;
		}
		while (array[i][j])
		{
			new_array_execve[i][j] = array[i][j];
			j++;
		}
		i++;
		j = 0;
	}
}

char	**child_array_execve(char **array)
{
	char	**new_array_execve;
	int		i;

	i = 0;
	while (array[i])
		i++;
	new_array_execve = ft_calloc(i + 1, sizeof(char *));
	if (!new_array_execve)
		return (NULL);
	child_array_execve_loop(array, new_array_execve);
	if (!new_array_execve)
		return (NULL);
	free_array(array);
	array = NULL;
	return (new_array_execve);
}

void	child2(t_minishell *mini, int n)
{
	char	*path_execve;
	char	**array_execve;

	array_execve = NULL;
	set_signal_for_process(mini);
	child_path(mini);
	manual_redirection(mini, n);
	path_execve = child_path_execve(mini->s_cmd->path);
	if (!array_execve)
		array_execve = child_array_execve(mini->s_cmd->cmd_arg);
	mini->s_cmd->cmd_arg = NULL;
	child_closenfree(mini);
	mini->exit_code = 0;
	if (path_execve == NULL)
		execve_failed(mini, path_execve, array_execve);
	if (path_execve[0] == '\0')
		execve_failed(mini, path_execve, array_execve);
	execve(path_execve, array_execve, mini->envp);
	execve_failed(mini, path_execve, array_execve);
}
