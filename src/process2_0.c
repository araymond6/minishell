/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:23:16 by araymond          #+#    #+#             */
/*   Updated: 2023/11/07 11:29:49 by vst-pier         ###   ########.fr       */
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

void	check_type_of_command(t_minishell *mini, int n)
{
	if (pipe(mini->s_cmd->pipe) == -1)
		message_perror("Impossible to create a pipe");
	if (mini->s_cmd->cmd_arg == NULL)
		null_command2(mini, n);
	else if (mini->s_cmd->cmd_arg[0] == NULL)
	{
		free(mini->s_cmd->cmd_arg);
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
			mini->exit_code = 1;
			n++;
			continue ;
		}
		find_cmd(mini, n);
		check_type_of_command(mini, n);
		n++;
	}
}

void	time_to_wait(t_minishell *mini)
{
	int				i;
	int				status;

	i = 0;
	while (i < mini->cmd_n)
	{
		if (mini->s_cmd->pids[i] != 0)
		{
			waitpid(mini->s_cmd->pids[i], &status, 0);
			if (mini->exit_code != 1)
			{
				mini->exit_code = WEXITSTATUS(status);
				if (mini->s_cmd->cmd_arg)
				{
					if (mini->exit_code == 1
						&& ft_strncmp(mini->s_cmd->cmd_arg[0], "exit", 5) != 0)
						mini->exit_code = 127;
				}
			}
		}
		i++;
	}
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
		i++;
	}
	return (0);
}
