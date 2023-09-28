/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:45:48 by vst-pier          #+#    #+#             */
/*   Updated: 2023/09/28 16:49:12 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// check if it<s a build0in or not and execute it
int	execute_cmd_buildin(t_minishell *mini)
{
	if (isbuildin(mini->s_cmd->cmd_arg[0]) == 0)
		execute_buildin(mini);
	else
	{
		if (execve(mini->s_cmd->path, mini->s_cmd->cmd_arg, NULL) == -1)
		{
			free(mini->s_cmd->path);
			free(mini->s_cmd->cmd_arg);
			return (message_perror("EXECVE"));
		}
	}
	return (0);
}

// parent side of the process
int	parent(t_cmd *cmd)
{
	if (cmd->prev->cmd != NULL)
	{
		if (dup2(cmd->prev->pipe_fd[0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	if (cmd->prev->cmd != NULL)
		close(cmd->prev->pipe_fd[0]);
	if (cmd->next->cmd == NULL)
		close(cmd->pipe_fd[0]);
	close(cmd->pipe_fd[1]);
	return (0);
}

// child side of the process - make the execution
int	child(t_minishell *mini)
{
	int	i;

	i = 0;
	if (mini->s_cmd->prev->cmd != NULL)
		if (dup2(mini->s_cmd->prev->pipe_fd[0], STDIN_FILENO) == -1)
			return(EXIT_FAILURE);
	if (mini->s_cmd->next->cmd != NULL && mini->s_cmd->next)
		if (dup2(mini->s_cmd->pipe_fd[1], STDOUT_FILENO) == -1)
			return(EXIT_FAILURE);
	if (mini->s_cmd->prev->cmd != NULL)
		close(mini->s_cmd->prev->pipe_fd[0]);
	if (mini->s_cmd->next->cmd == NULL)
		close(mini->s_cmd->pipe_fd[0]);
	close(mini->s_cmd->pipe_fd[1]);
	//free(cmd->pipe_fd);
	if (mini->s_cmd->redir)
	{
		while (mini->s_cmd->redir[i])
		{
			change_inf(mini->s_cmd, mini->s_cmd->redir[i], mini->s_cmd->file[i]);
			change_out(mini->s_cmd, mini->s_cmd->redir[i], mini->s_cmd->file[i]);
			i++;
		}
	}
	execute_cmd_buildin(mini);
	return (0);
}

// the processus
int	process(t_minishell *mini)
{
	pid_t	pid;
	t_cmd	*temp;
	int 	fd_stdin_out[2];
	
	pid = 1;
	while (mini->s_cmd->next)
	{
		if (pipe(mini->s_cmd->pipe_fd) == -1)
			return(message_perror("Pipe"));
		if (pid != 0)
		{
			pid = fork();
			if (pid == -1)
				return(message_perror("Fork"));
			if (pid == 0)
				child(mini);
			if (pid != 0)
				parent(mini->s_cmd);
			mini->s_cmd = mini->s_cmd->next;
		}
	}
	waitpid(pid, &mini->s_cmd->status, 0);
	if (WEXITSTATUS(mini->s_cmd->status) == 1)
		message_perror("WEXITSTATUS");
	return (0);
}
