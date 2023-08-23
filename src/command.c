/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerie <valerie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:34:51 by vst-pier          #+#    #+#             */
/*   Updated: 2023/08/23 17:55:08 by valerie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// joindre les path avec la commande
void	join_path_command(char **possible_path, char *command)
{
	int	index_path;

	index_path = 0;
	while (possible_path[index_path])
	{
		possible_path[index_path] = ft_strjoin(possible_path[index_path], "/");
		index_path++;
	}
	index_path = 0;
	while (possible_path[index_path])
	{
		possible_path[index_path] = ft_strjoin(possible_path[index_path], command);
		index_path++;
	}
}

//trouver le bon path (commande seulement)
char	*test_path(char **possible_path)
{
	int		index_possible_path;
	char	*good_path;
	int		path_len;

	index_possible_path = 0;
	while (possible_path[index_possible_path])
	{
		if (access(possible_path[index_possible_path], X_OK) == 0)
		{
			path_len = ft_strlen(possible_path[index_possible_path]) + 1;
			good_path = ft_calloc(path_len, sizeof(char));
			if (!good_path)
				return (NULL);
			ft_strlcpy(good_path, possible_path[index_possible_path], path_len);
			return (good_path);
		}
		index_possible_path++;
	}
	return (NULL);
}

//fct qui verifie si cest un buildin et qui assigne le buildin comme path
int isbuildin(char *isbuildin)
{
	if(ft_strncmp(isbuildin, "echo", 4) == 0
		|| ft_strncmp(isbuildin, "cd", 2) == 0
		|| ft_strncmp(isbuildin, "pwd", 3) == 0
		|| ft_strncmp(isbuildin, "export", 6) == 0
		|| ft_strncmp(isbuildin, "unset", 5) == 0
		|| ft_strncmp(isbuildin, "env", 3) == 0
		|| ft_strncmp(isbuildin, "exit", 4) == 0)
		return(0);
	return(1);
}

//trouver le bon path (commande seulement ou path rel. abs.)
int find_path(t_minishell *mini)
{
	char **possible_path;
	int len;

	if(access(mini->struct_cmd->cmd, X_OK) == 0 || isbuildin(mini->struct_cmd->cmd) == 0)
	{	
		len = ft_strlen(mini->struct_cmd->cmd);
		mini->struct_cmd->path = ft_calloc((len + 1), sizeof(char));
		if (!mini->struct_cmd->path)
			return (-1);
		ft_strlcpy(mini->struct_cmd->path, mini->struct_cmd->cmd, len + 1);
	}
	else
	{
		possible_path = ft_split(mini->path_envp, ':');
		join_path_command(possible_path, mini->struct_cmd->cmd);
		mini->struct_cmd->path = test_path(possible_path);
		free_array(possible_path);
	}
	return(0);
}

//function qui va assigner dans la structure t_cmd les don/es lies a la commande pour le processus
int check_command(t_minishell *mini, int i, int j)
{
	int len_cmd;
	int len;
	int len_redir;

	len_cmd = len_until_space(mini, i, j);
	mini->struct_cmd->cmd = ft_calloc(len_cmd + 1, sizeof(char));
	j = ft_strjcpy(mini->struct_cmd->cmd, mini->cmd[i], len_cmd, j);
	if(mini->cmd[i][j] == ' ')
		j++;
	if(find_path(mini) == -1)
		return(-1);
	len = ft_strlen(mini->struct_cmd->path);
	mini->struct_cmd->cmd_arg = ft_calloc(3, sizeof(char*));
	if (!mini->struct_cmd->cmd_arg)
		return (-1);
	mini->struct_cmd->cmd_arg[0] = ft_calloc(len + 1, sizeof(char));
	if (!mini->struct_cmd->cmd_arg[0])
		return (-1);
	ft_strlcpy(mini->struct_cmd->cmd_arg[0], mini->struct_cmd->path, len + 1);
	len_redir = len_until_redirections(mini, i, j);
	mini->struct_cmd->cmd_arg[1] = ft_calloc(len_redir + 1, sizeof(char));
	if (!mini->struct_cmd->cmd_arg[1])
		return (-1);
	j = ft_strjcpy(mini->struct_cmd->cmd_arg[1], mini->cmd[i], len_redir, j);
	return(j);
}