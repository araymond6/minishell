/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerie <valerie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:30:12 by vst-pier          #+#    #+#             */
/*   Updated: 2023/08/24 11:35:20 by valerie          ###   ########.fr       */
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
//function qui initilaize la struct cmd
void initialize_struct_cmd(t_cmd *struct_cmd)
{
	struct_cmd->redir = NULL;
	struct_cmd->cmd = NULL;
	struct_cmd->path = NULL;
	struct_cmd->cmd_arg = NULL;
	struct_cmd->file = NULL;
	struct_cmd->next = NULL;
	struct_cmd->nb_redir = 0;
	struct_cmd->prev = ft_calloc(1, sizeof(t_cmd));
}

//function qui compte le nb de caractere avant la prochaine espace
int len_until_space(t_minishell *mini, int i, int j)
{
	int len;
	
	len = 0;
	while(mini->cmd[i][j+ len] != ' ' && mini->cmd[i][j+ len] != '>'
		&& mini->cmd[i][j+ len] != '<' && mini->cmd[i][j+ len])
		len++;
	return(len);
}

//function qui compte le nb de caractere avant la prochaine redirection
int len_until_redirections(t_minishell *mini, int i, int j)
{
	int len;
	
	len = 0;
	while(mini->cmd[i][j+ len] != '<' && mini->cmd[i][j+ len] != '>' && mini->cmd[i][j+ len])
		len++;
	return(len);
}

//copie mini->cmd a partir de j pour max caracteres
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

int	message_perror(char *str)
{
	perror(str);
	return (EXIT_FAILURE);
}