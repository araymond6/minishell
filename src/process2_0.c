#include "../include/minishell.h"

int	parent2(t_minishell *mini)
{
	if (dup2(mini->s_cmd->pipe[0], STDIN_FILENO) == -1)
		message_perror("Impossible to read in the pipe");
	close(mini->s_cmd->pipe[0]);
	close(mini->s_cmd->pipe[1]);
	return (0);
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
		if (pipe(mini->s_cmd->pipe) == -1)
			message_perror("Impossible to create a pipe");
		if (mini->s_cmd->cmd_arg == NULL)
			null_command2(mini, n); ////////
		else if (mini->s_cmd->cmd_arg[0] == NULL)
		{
			free(mini->s_cmd->cmd_arg);
			mini->s_cmd->cmd_arg = NULL;
			null_command2(mini, n); ///////
		}
		else if (isbuildin(mini->s_cmd->cmd_arg[0]) == 0)
			exec_buildin2(mini, n); ///////
		else
			exec_bash_cmd(mini, n);
		n++;
	}
	return (0);
}

void	time_to_execute(t_minishell *mini)
{
	int		i;

	i = 0;
	mini->s_cmd = ft_calloc(1, sizeof(t_cmd));
	initialize_s_cmd(mini);
	all_here_doc2(mini);
	forker2(mini);
	while (i < mini->cmd_n)
	{
		if (mini->s_cmd->pids[i] != 0)
		{
			waitpid(mini->s_cmd->pids[i], &mini->s_cmd->status[i], 0);
			i++;
		}
		else
			continue ;
	}
	dup2(mini->s_cmd->fd_stdin, STDIN_FILENO);
	dup2(mini->s_cmd->fd_stdout, STDOUT_FILENO);
	close(mini->s_cmd->fd_stdin);
	close(mini->s_cmd->fd_stdout);
	free_scmd(mini->s_cmd);
}