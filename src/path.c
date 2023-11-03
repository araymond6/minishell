/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:16:26 by araymond          #+#    #+#             */
/*   Updated: 2023/11/03 18:27:15 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	join_path_command2(char **path, char *command)
{
	int		i_path;
	char	*path1;

	i_path = 0;
	if (!path)
	{
		message_perror("impossible to find PATH in the envp");
		return ;
	}
	while (path[i_path])
	{
		path1 = path[i_path];
		path[i_path] = ft_strjoin(path1, "/");
		path1 = free_n_null(path1);
		i_path++;
	}
	i_path = 0;
	while (path[i_path])
	{
		path1 = path[i_path];
		path[i_path] = ft_strjoin(path1, command);
		path1 = free_n_null(path1);
		i_path++;
	}
}

char	*test_path2(char **path)
{
	int		i_path;
	char	*good_path;
	int		path_len;

	i_path = 0;
	if (!path)
		return (NULL);
	while (path[i_path])
	{
		if (access(path[i_path], X_OK) == 0)
		{
			path_len = ft_strlen(path[i_path]) + 1;
			good_path = ft_calloc(path_len, sizeof(char));
			if (!good_path)
				return (NULL);
			ft_strlcpy(good_path, path[i_path], path_len);
			return (good_path);
		}
		i_path++;
	}
	return (NULL);
}

void	find_path2(t_minishell *mini)
{
	int		len;
	char	**tab_path;

	if (access(mini->s_cmd->cmd_arg[0], X_OK) == 0)
	{
		len = ft_strlen(mini->s_cmd->cmd_arg[0]);
		mini->s_cmd->path = ft_calloc((len + 1), sizeof(char));
		if (!mini->s_cmd->path)
			mini->s_cmd->path = NULL;
		if (!mini->s_cmd->path)
		{
			message_perror("Malloc error");
			return ;
		}
		ft_strlcpy(mini->s_cmd->path, mini->s_cmd->cmd_arg[0], len + 1);
	}
	else
	{
		tab_path = ft_split(mini->path + 5, ':');
		join_path_command2(tab_path, mini->s_cmd->cmd_arg[0]);
		mini->s_cmd->path = test_path2(tab_path);
		free_array(tab_path);
		tab_path = NULL;
	}
}
