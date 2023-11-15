/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:23:16 by araymond          #+#    #+#             */
/*   Updated: 2023/11/15 10:12:34 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parent2(t_minishell *mini)
{
	if (dup2(mini->s_cmd->pipe[0], STDIN_FILENO) == -1)
		message_perror("Impossible to read in the pipe");
	close(mini->s_cmd->pipe[0]);
	close(mini->s_cmd->pipe[1]);
	return (0);
}

int	find_first_command(t_minishell *mini, int n)
{
	int	i;

	i = 0;
	while (i < mini->token_count && mini->token[i].cmd_n != n)
	{
		i++;
	}
	while (i < mini->token_count && mini->token[i].cmd_n == n)
	{
		if (mini->token[i].type != STRING)
			i += 2;
		else
			return (i);
	}
	return (i);
}

void	check_type_of_command(t_minishell *mini, int n)
{
	int	i;

	i = find_first_command(mini, n);
	if (pipe(mini->s_cmd->pipe) == -1)
		message_perror("Impossible to create a pipe");
	if (mini->s_cmd->cmd_arg == NULL)
		null_command2(mini, n);
	else if (mini->s_cmd->cmd_arg[0] == NULL)
	{
		free_array(mini->s_cmd->cmd_arg);
		mini->s_cmd->cmd_arg = NULL;
		null_command2(mini, n);
	}
	else if (mini->s_cmd->cmd_arg[0][0] == 0 && mini->token[i].inquote == 0)
	{
		free_array(mini->s_cmd->cmd_arg);
		mini->s_cmd->cmd_arg = NULL;
		null_command2(mini, n);
	}
	else if (isbuildin(mini->s_cmd->cmd_arg[0]) == 0 && mini->cmd_n == 1)
		exec_buildin2(mini, n);
	else
		exec_bash_cmd(mini, n);
}

void	forker2(t_minishell *mini)
{
	int	r;
	int	n;

	r = 0;
	n = 1;
	while (n <= mini->cmd_n)
	{
		clear_s_cmd(mini->s_cmd);
		mini->exit_code = 0;
		if (check_redirect_input(mini, n) == 1)
		{
			if (pipe(mini->s_cmd->pipe) == -1)
				message_perror("Impossible to create a pipe");
			else
				parent2(mini);
			mini->exit_code = 1;
			n++;
			continue ;
		}
		find_cmd(mini, n);
		check_type_of_command(mini, n);
		n++;
	}
}

static int	check_valid_output(t_minishell *mini, int *i)
{
	int	fd;

	if (mini->token[*i].type == REDIRECT_OUTPUT)
	{
		(*i)++;
		fd = open(mini->token[*i].token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			message_perror(mini->token[*i].token);
			return (1);
		}
		close(fd);
	}
	else if (mini->token[*i].type == APPEND)
	{
		(*i)++;
		fd = open(mini->token[*i].token, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			message_perror(mini->token[*i].token);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	check_redirect_input(t_minishell *mini, int n)
{
	int	i;
	int	fd;

	i = 0;
	while (i < mini->cmd_n && mini->token[i].cmd_n != n)
		i++;
	while (i < mini->token_count && mini->token[i].cmd_n == n)
	{
		if (mini->token[i].type == REDIRECT_INPUT)
		{
			i++;
			fd = open(mini->token[i].token, O_RDONLY);
			if (fd == -1)
			{
				message_perror(mini->token[i].token);
				return (1);
			}
			close(fd);
		}
		if (check_valid_output(mini, &i) == 1)
			return (1);
		i++;
	}
	return (0);
}
