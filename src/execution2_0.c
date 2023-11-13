/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:17:07 by araymond          #+#    #+#             */
/*   Updated: 2023/11/13 13:04:37 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	null_command2(t_minishell *mini, int n)
{
	int	i;

	i = 0;
	if (dup2(mini->s_cmd->pipe[0], STDIN_FILENO) == -1)
		message_perror("Impossible to read in the pipe");
	close(mini->s_cmd->pipe[0]);
	manual_redirection(mini, n);
	clear_s_cmd(mini->s_cmd);
}

void	exec_buildin2(t_minishell *mini, int n)
{
	int	i;

	i = 0;
	if (dup2(mini->s_cmd->pipe[0], STDIN_FILENO) == -1)
		message_perror("Impossible to read in the pipe");
	close(mini->s_cmd->pipe[0]);
	if (n < mini->cmd_n)
	{
		if (dup2(mini->s_cmd->pipe[1], STDOUT_FILENO) == -1)
			message_perror("Impossible to write in the pipe");
		close(mini->s_cmd->pipe[1]);
	}
	else if (n == mini->cmd_n && mini->cmd_n != 1)
	{
		if (dup2(mini->s_cmd->fd_stdout, STDOUT_FILENO) == -1)
			message_perror("Impossible to write in the pipe");
		close(mini->s_cmd->pipe[1]);
	}
	else
		close(mini->s_cmd->pipe[1]);
	while (i < mini->token_count && mini->token[i].cmd_n != n)
		i++;
	manual_redirection_loop(mini, n, i);
	execute_buildin(mini);
	clear_s_cmd(mini->s_cmd);
}

void	build_in_a_child(t_minishell *mini, int n)
{
	int	j;

	j = 0;
	close(mini->s_cmd->pipe[0]);
	redirect_the_output(mini, n);
	while (j < mini->token_count && mini->token[j].cmd_n != n)
		j++;
	manual_redirection_loop(mini, n, j);
	execute_buildin(mini);
	if (mini->envpset == 1)
		free_array(mini->envp);
	clear_mini(mini);
	close(mini->s_cmd->fd_stdin);
	close(mini->s_cmd->fd_stdout);
	free_scmd(mini->s_cmd);
	exit(0);
}

void	exec_bash_cmd(t_minishell *mini, int n)
{
	int	i;

	i = 0;
	while (mini->s_cmd->pids[i] != 0 && i < mini->cmd_n)
		i++;
	mini->s_cmd->pids[i] = fork();
	if (mini->s_cmd->pids[i] < 0)
	{
		message_perror("Crash in the fork function");
		clear_s_cmd(mini->s_cmd);
	}
	else if (mini->s_cmd->pids[i] == 0
		&& isbuildin(mini->s_cmd->cmd_arg[0]) == 0)
		build_in_a_child(mini, n);
	else if (mini->s_cmd->pids[i] == 0)
		child2(mini, n);
	else
		parent2(mini);
}
