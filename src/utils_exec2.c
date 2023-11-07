/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:16:03 by araymond          #+#    #+#             */
/*   Updated: 2023/11/07 13:10:06 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	supp_here_doc_file(t_minishell *mini)
{
	int		n;
	int		i;
	char	*new_file_name;

	n = 0;
	i = mini->heredoc_count;
	mini->heredoc_count = 0;
	while (n < mini->token_count && i > mini->heredoc_count)
	{
		if (mini->token[n].type == HERE_DOC)
		{
			new_file_name = create_here_doc_name(mini->heredoc_count);
			unlink(new_file_name);
			free(new_file_name);
			mini->heredoc_count++;
		}
		n++;
	}
}

int	initialize_s_cmd(t_minishell *mini)
{
	int	n;

	n = 0;
	mini->s_cmd->path = NULL;
	mini->s_cmd->cmd_arg = NULL;
	mini->s_cmd->pids = ft_calloc(mini->cmd_n, sizeof(pid_t));
	if (!mini->s_cmd->pids)
		return (1);
	mini->s_cmd->narg = 0;
	mini->s_cmd->fd_stdin = dup(STDIN_FILENO);
	mini->s_cmd->fd_stdout = dup(STDOUT_FILENO);
	return (0);
}

void	free_scmd(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->path)
			cmd->path = free_n_null(cmd->path);
		if (cmd->cmd_arg)
		{
			free_array(cmd->cmd_arg);
			cmd->cmd_arg = NULL;
		}
		if (cmd->pids)
		{
			free(cmd->pids);
			cmd->pids = NULL;
		}
		free(cmd);
		cmd = NULL;
	}
}

void	clear_s_cmd(t_cmd *cmd)
{
	if (cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
	if (cmd->cmd_arg)
	{
		free_array(cmd->cmd_arg);
		cmd->cmd_arg = NULL;
	}
	cmd->narg = 0;
}

char	*create_here_doc_name(int count)
{
	char	*file_name;
	char	*new_file_name;

	file_name = ft_itoa(count);
	if (!file_name)
		return (printf("Impossible to execute here_doc"), NULL);
	new_file_name = ft_strjoin(file_name, "..txt");
	if (!new_file_name)
		return (printf("Impossible to execute here_doc"), NULL);
	free(file_name);
	return (new_file_name);
}
