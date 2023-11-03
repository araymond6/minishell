/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:23:16 by araymond          #+#    #+#             */
/*   Updated: 2023/11/03 18:27:15 by araymond         ###   ########.fr       */
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

int	forker2(t_minishell *mini)
{
	int	r;
	int	n;

	r = 0;
	n = 1;
	while (n <= mini->cmd_n)
	{
		find_cmd(mini, n);
		check_type_of_command(mini, n);
		n++;
	}
	return (0);
}

void	time_to_wait(t_minishell *mini)
{
	int	i;
	int	status;

	i = 0;
	while (i < mini->cmd_n)
	{
		if (mini->s_cmd->pids[i] != 0)
		{
			waitpid(mini->s_cmd->pids[i], &status, 0);
		}
		i++;
	}
}
