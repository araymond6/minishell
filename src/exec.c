/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:45:48 by vst-pier          #+#    #+#             */
/*   Updated: 2023/08/04 16:27:17 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void create_tab_file(t_minishell *mini)
{
	int i;
	
	i = 0;
	if(!mini->struct_cmd->file)
	{
		mini->struct_cmd->file = ft_calloc(mini->struct_cmd->nb_redir + 1, sizeof(char*));
		while(i <= mini->struct_cmd->nb_redir)
		{
			mini->struct_cmd->file[i] = ft_calloc( 2, sizeof(char));
			mini->struct_cmd->file[i] = NULL;
			i++;
		}
	}
	if(!mini->struct_cmd->redir)
		mini->struct_cmd->redir = ft_calloc(mini->struct_cmd->nb_redir + 1, sizeof(char));
}

void assign_redir_values(t_minishell *mini, char c)
{
	int k;
	
	k = 0;
	while(mini->struct_cmd->redir[k])
		k++;
	mini->struct_cmd->redir[k] = c;
}

void	here_doc_func(t_minishell *mini, int i, int j)
{
	create_tab_file(mini);
	assign_redir_values(mini, '2');
}

int space_len(t_minishell *mini, int i, int j)
{
	int len;
	
	len = 0;
	while(mini->cmd[i][j+ len] != ' ')
		len++;
	return(len);
}

int	std_entry_redirection(t_minishell *mini, int i, int j)
{		
	int len;
	int r;
	int copy;
	int index;

	len = 0;
	r = 0;
	copy = 0;
	index = 0;
	create_tab_file(mini);
	assign_redir_values(mini, '1');
	len = space_len(mini, i, j);
	while(mini->struct_cmd->file[r])
		r++;
	while(copy < len)	
	{
		mini->struct_cmd->file[r][index] = mini->cmd[i][j + index];
		index++;
	}
	return(j + index);
	
}
void	error(t_minishell *mini, int i, int j)
{
}
void	append_redirection(t_minishell *mini, int i, int j)
{
	create_tab_file(mini);
	assign_redir_values(mini, '4');
}
void	std_exit_redirection(t_minishell *mini, int i, int j)
{
	create_tab_file(mini);
	assign_redir_values(mini, '3');
}

int	entry_redirection(t_minishell *mini, int i, int j)
{
		
	if(mini->cmd[i][j] == '<')
		here_doc_func(mini, i, j + 1);
	else if(mini->cmd[i][j] == ' ')
		j = std_entry_redirection(mini, i, j + 1);
	else if(mini->cmd[i][j] == '>')
		error(mini, i, j);
	else
		std_entry_redirection(mini, i, j);
	return(j);
}
	
void	exit_redirection(t_minishell *mini, int i, int j)
	{
		if(mini->cmd[i][j] == '>')
			append_redirection(mini, i, j + 1);
		else if(mini->cmd[i][j] == ' ')
			std_exit_redirection(mini, i, j + 1);
		else if(mini->cmd[i][j] == '<')
			error(mini, i, j);
		else
			std_exit_redirection(mini, i, j);
	}

void check_command(t_minishell *mini, int i, int j)
	{
		
	}

void initialize_struct_cmd(t_cmd *struct_cmd)
{
	struct_cmd->redir = NULL;
	struct_cmd->cmd = NULL;
	struct_cmd->path = NULL;
	struct_cmd->cmd_arg = NULL;
	struct_cmd->file = NULL;
	struct_cmd->next = NULL;
	struct_cmd->delimiter = NULL;
	struct_cmd->nb_redir = 0;
}

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

void parsing_command(t_minishell *mini, int i)
{
	t_cmd *command;
	int j;
	
	j = 0;
	command = ft_calloc(1, sizeof(t_cmd));
	mini->struct_cmd = command;
	initialize_struct_cmd(mini->struct_cmd);
	while(mini->cmd[i][j])
	{
		mini->struct_cmd->nb_redir = redir_count(mini->cmd[i]);
		if(mini->cmd[i][j] == '<')
			j = entry_redirection(mini, i, j + 1);
		else if(mini->cmd[i][j] == '>')
			exit_redirection(mini, i, j + 1);
		else if(mini->cmd[i][j] == ' ')
			j++;
		else 
			check_command(mini, i, j);
	}
}

void execution(t_minishell *mini)
{
	int i;
	
	i = 0;
	while(mini->cmd[i] != NULL)
	{
		parsing_command(mini, i);
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_minishell *mini;
	
	(void) argc;
	(void) argv;
	mini = ft_calloc(1, sizeof(t_minishell));
	save_path(mini, envp);
	mini->arg = NULL;
	mini->cmd = ft_calloc(4, sizeof(char*));
	mini->cmd[0] = ft_calloc(28, sizeof(char));
	mini->cmd[0] = "< allo.txt ls -la >> txt.txt";
	mini->cmd[1] = ft_calloc(16, sizeof(char));
	mini->cmd[1] = "cat -e >txt.txt";
	mini->cmd[2] = ft_calloc(12, sizeof(char));
	mini->cmd[2] = "<<END wc -l";
	mini->cmd[3] = ft_calloc(1, sizeof(char));
	mini->cmd[3] = NULL;
	mini->struct_cmd = NULL;
	execution(mini);
}