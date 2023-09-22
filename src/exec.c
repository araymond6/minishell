/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:45:48 by vst-pier          #+#    #+#             */
/*   Updated: 2023/09/22 14:14:28 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// check if it<s a build0in or not and execute it
int	execute_cmd_buildin(t_cmd *cmd)
{
	if (isbuildin(cmd->cmd_arg[0]) == 0)
		execute_buildin(cmd);
	else
	{
		if (execve(cmd->path, cmd->cmd_arg, NULL) == -1)
			return (message_perror("EXECVE"));
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
int	child(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->prev->cmd != NULL)
		if (dup2(cmd->prev->pipe_fd[0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
	if (cmd->next->cmd != NULL)
		if (dup2(cmd->pipe_fd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	if (cmd->prev->cmd != NULL)
		close(cmd->prev->pipe_fd[0]);
	if (cmd->next->cmd == NULL)
		close(cmd->pipe_fd[0]);
	close(cmd->pipe_fd[1]);
	//free(cmd->pipe_fd);
	if (cmd->redir)
	{
		while (cmd->redir[i])
		{
			change_inf(cmd, cmd->redir[i], cmd->file[i]);
			change_out(cmd, cmd->redir[i], cmd->file[i]);
			i++;
		}
		//free(cmd->redir);
		//free_array(cmd->file);
	}
	execute_cmd_buildin(cmd);
	return (0);
}

// the processus
int	process(t_cmd *cmd)
{
	pid_t	pid;

	pid = 1;
	while (cmd->next)
	{
		if (pipe(cmd->pipe_fd) == -1)
			exit(message_perror("Pipe"));
		if (pid != 0)
		{
			pid = fork();
			if (pid == -1)
				exit(message_perror("Fork"));
			if (pid == 0)
				child(cmd);
			if (pid != 0)
				parent(cmd);
			cmd = cmd->next;
		}
	}
	//on free le contenu de toutes les nodes et les nodes
	waitpid(pid, &cmd->status, 0);
	if (WEXITSTATUS(cmd->status) == 1)
		message_perror("WEXITSTATUS");
	return (0);
}
