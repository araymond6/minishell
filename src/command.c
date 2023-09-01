/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerie <valerie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:34:51 by vst-pier          #+#    #+#             */
/*   Updated: 2023/09/01 13:08:59 by valerie          ###   ########.fr       */
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

int nbr_arg(t_minishell *mini, int i, int j)
{
	int space;
	int k;
	
	space = 0;
	k = 0;
	while(mini->cmd[i][j+ k] && mini->cmd[i][j+ k] != '>' && mini->cmd[i][j+ k] != '<')
	{	
		if(mini->cmd[i][j+ k] == ' ' && mini->cmd[i][j+ k + 1] != '>' && mini->cmd[i][j+ k + 1] != '<')
			space++;
		k++;
	}
	return(space);
}

int cmd_to_struct_cmd_cmd(t_minishell *mini, int i, int j)
{
	int len_cmd;
	
	len_cmd = len_until_space(mini, i, j);
	mini->struct_cmd->cmd = ft_calloc(len_cmd + 1, sizeof(char));
	j = ft_strjcpy(mini->struct_cmd->cmd, mini->cmd[i], len_cmd, j);
	return(j);
}

int cmd_to_struct_cmd_arg_cmd_first(t_minishell *mini, int i, int j)
{
	int len;
	
	len = ft_strlen(mini->struct_cmd->path);
	mini->struct_cmd->cmd_arg[0] = ft_calloc(len + 1, sizeof(char));
	if (!mini->struct_cmd->cmd_arg[0])
		return (-1);
	ft_strlcpy(mini->struct_cmd->cmd_arg[0], mini->struct_cmd->path, len + 1);
	return(0);
}


int cmd_to_struct_cmd_arg_cmd_middle(t_minishell *mini, int i, int j, int k)
{
	int len;
	
	len = len_until_space(mini, i, j);
	printf("char : %c\n", mini->cmd[i][j]);
	printf("char : %d\n", j);
	mini->struct_cmd->cmd_arg[k] = ft_calloc(len + 1, sizeof(char));
	if (!mini->struct_cmd->cmd_arg[k])
		return (-1);
	j = ft_strjcpy(mini->struct_cmd->cmd_arg[k], mini->cmd[i], len, j);
	if(mini->cmd[i][j] == ' ')
		j++;
	return(j);
}

int cmd_to_struct_cmd_arg_cmd_end(t_minishell *mini, int i, int j, int k)
{
	int len_space;
	int len_redirection;
	int len;

	len_space = len_until_space(mini, i, j);
	len_redirection = len_until_redirections(mini, i, j);
	if(len_space < len_redirection)
		len = len_space;
	else
		len = len_redirection;
	mini->struct_cmd->cmd_arg[k] = ft_calloc(len + 1, sizeof(char));
	if (!mini->struct_cmd->cmd_arg[k])
		return (-1);
	j = ft_strjcpy(mini->struct_cmd->cmd_arg[k], mini->cmd[i], len, j);
	if(mini->cmd[i][j] == ' ')
		j++;
	return(j);
}


//function qui va assigner dans la structure t_cmd les donns lies a la commande pour le processus
int check_command(t_minishell *mini, int i, int j)
{
	int nbr_of_arg;
	int k;
	
	j = cmd_to_struct_cmd_cmd(mini, i, j);
	if(find_path(mini) == -1)
		return(-1);
	nbr_of_arg = nbr_arg(mini, i, j);
	mini->struct_cmd->cmd_arg = ft_calloc(nbr_of_arg + 2, sizeof(char*));
	if(mini->cmd[i][j] == ' ')
		j++;
	if (!mini->struct_cmd->cmd_arg)
		return (-1);
	if(cmd_to_struct_cmd_arg_cmd_first(mini, i, j) == -1)
		return(-1);
	k = 1;
	if(nbr_of_arg > 0)
	{
		while( k < nbr_of_arg)
		{
			j = cmd_to_struct_cmd_arg_cmd_middle(mini, i, j, k);
			if(j == -1)
				return(-1);
			k++;
		}
		j = cmd_to_struct_cmd_arg_cmd_end(mini, i, j, k);
		if(j == -1)
			return(-1);
	}
	printf("%s\n", mini->struct_cmd->cmd_arg[0]);
	printf("%s\n", mini->struct_cmd->cmd_arg[1]);
	return(j);
}

