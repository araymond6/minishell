#include "../include/minishell.h"

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

char	*free_n_null(char *array)
{
	free(array);
	array = NULL;
	return (NULL);
}
