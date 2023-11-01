#include "../include/minishell.h"

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

//free an array
void	free_array(char **array)
{
	int	index_array;

	index_array = 0;
	if (!array)
		return ;
	while (array[index_array])
	{
		free(array[index_array]);
		array[index_array] = NULL;
		index_array++;
	}
	free(array);
	array = NULL;
}

//write the error code after str
int	message_perror(char *str)
{
	perror(str);
	return (EXIT_FAILURE);
}

void	execve_failed(char *path_execve, char **array_execve)
{
	message_perror("Impossible to execute the command: ");
	free(path_execve);
	free_array(array_execve);
	exit(1);
}

void	child_closenfree(t_minishell *mini)
{
	if (mini->s_cmd)
	{
		if (mini->s_cmd->path)
		{
			free(mini->s_cmd->path);
			mini->s_cmd->path = NULL;
		}
		if (mini->s_cmd->cmd_arg)
		{
			free_array(mini->s_cmd->cmd_arg);
			mini->s_cmd->cmd_arg = NULL;
		}
		if (mini->s_cmd->status)
		{
			free(mini->s_cmd->status);
			mini->s_cmd->status = NULL;
		}
		close(mini->s_cmd->fd_stdin);
		close(mini->s_cmd->fd_stdout);
		if (mini->s_cmd->pids)
		{
			free(mini->s_cmd->pids);
			mini->s_cmd->pids = NULL;
		}
		free(mini->s_cmd);
		mini->s_cmd = NULL;
		clear_mini(mini);
	}
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
		if (cmd->status)
		{
			free(cmd->status);
			cmd->redir = NULL;
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

char	*free_n_null(char *array)
{
	free(array);
	array = NULL;
	return (NULL);
}
