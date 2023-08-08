/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:30:12 by vst-pier          #+#    #+#             */
/*   Updated: 2023/08/08 15:04:49 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
}

//function qui compte le nb de caractere avant la prochaine espace
int len_until_space(t_minishell *mini, int i, int j)
{
	int len;
	
	len = 0;
	while(mini->cmd[i][j+ len] != ' ' && mini->cmd[i][j+ len] != '>'
		&& mini->cmd[i][j+ len] != '<')
		len++;
	return(len);
}

//function qui compte le nb de caractere avant la prochaine redirection
int len_until_redirections(t_minishell *mini, int i, int j)
{
	int len;
	
	len = 0;
	while(mini->cmd[i][j+ len] != '<' && mini->cmd[i][j+ len] != '>')
		len++;
	return(len);
}

//function qui gere les erreurs
void	error(t_minishell *mini, int i, int j)
{
}

//function qui compte le nb de redirection quil y aura
int	redir_count(char *cmd)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(cmd[i])
	{
		if (cmd[i] == '<')
		{
			count += 1;
			if (cmd[i + 1] == '<')
				i++;
		}
		else if (cmd[i] == '>')
		{
			count += 1;
			if (cmd[i + 1] == '>')
				i++;
		}
		i++;
	}
	return(count);
}

//function qui parse la commande afin doute les commandes de mini dans la structure cmd
void parsing_command(t_minishell *mini, int i)
{
	t_cmd *command;
	int j;
	
	j = 0;
	command = ft_calloc(1, sizeof(t_cmd));
	mini->struct_cmd = command;
	initialize_struct_cmd(mini->struct_cmd);
	mini->struct_cmd->nb_redir = redir_count(mini->cmd[i]);
	while(mini->cmd[i][j])
	{
		if(mini->cmd[i][j] == '<')
			{j = entry_redirection(mini, i, j + 1);
			write(1, "allo", 4);}
		else if(mini->cmd[i][j] == '>')
			{j = exit_redirection(mini, i, j + 1);
		write(1, "allo", 4);}
		else if(mini->cmd[i][j] == ' ')
			j++;
		else if(mini->cmd[i][j] == '\n')
		{
			i++;
			j = 0;
		}
		else 
			j = check_command(mini, i, j);
	}
}