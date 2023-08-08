/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:34:51 by vst-pier          #+#    #+#             */
/*   Updated: 2023/08/08 16:03:07 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//function qui free un array
void	free_array(char **array)
{
	int	index_array;

	index_array = 0;
	while (array[index_array])
	{
		free(array[index_array]);
		array[index_array] = NULL;
		index_array++;
	}
	free(array);
	array = NULL;
}

//function qui malloc les array des redirections redir, mais aussi le char **file qui va contenir le nom du fichier lie a la redirection
void create_tab_file(t_minishell *mini)
{
	int i;
	
	i = 0;
	if(!mini->struct_cmd->file)
	{
		mini->struct_cmd->file = ft_calloc(mini->struct_cmd->nb_redir + 1, sizeof(char*));
		while(i < mini->struct_cmd->nb_redir + 1)
		{
			mini->struct_cmd->file[i] = ft_calloc(1, sizeof(char));
			i++;
		}
	}
	if(!mini->struct_cmd->redir)
		mini->struct_cmd->redir = ft_calloc(mini->struct_cmd->nb_redir + 1, sizeof(char));
}

//function qui va mettre dans char *redir la sorte de redirection
void assign_redir_values(t_minishell *mini, char c)
{
	int k;
	
	k = 0;
	while(mini->struct_cmd->redir[k])
		k++;
	mini->struct_cmd->redir[k] = c;
}

//function qui va assigner les chose en cas de >> ou de >
int	entry_redirection(t_minishell *mini, int i, int j)
{
		
	if(mini->cmd[i][j] == '<')
		here_doc_func(mini, i, j + 1);
	else if(mini->cmd[i][j] == ' ')
		j = redirection13(mini, i, j + 1, '1');
	else if(mini->cmd[i][j] == '>')
		error(mini, i, j);
	else 
		j = redirection13(mini, i, j, '1');
	return(j);
}

//function qui va assigner les chose en cas de >> ou de >
int	exit_redirection(t_minishell *mini, int i, int j)
	{
		if(mini->cmd[i][j] == '>')
			append_redirection(mini, i, j + 1);
		else if(mini->cmd[i][j] == ' ')
			j = redirection13(mini, i, j + 1, '3');
		else if(mini->cmd[i][j] == '<')
			error(mini, i, j);
		else
			j = redirection13(mini, i, j, '3');
		return(j);
	}


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

//part 2 de find_path
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

//trouver le bon path (commande seulement ou path rel. abs.)
int find_path(t_minishell *mini)
{
	char **possible_path;
	int len;
	
	if(access(mini->struct_cmd->cmd, X_OK) == 0)
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

int ft_strjcpy(char *dst, char *src, int max, int j)
{
	int i;

	i = 0;
	while(i < max)
	{
		dst[i] = src[j + i];
		i++;
	}
	return (j + i);
}

//function qui va assigner les chose quand il trouve la commande
//peut recevoir le path absolue, mais aussi le path relatif ou bien encore seulement le nom de la commande 
//utiliser acces pou verifier comment elle fonctionne.
// struct_cmd->**cmd_arg = NULL;
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
		return(error(mini, i, j), -1);
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