#include "../include/minishell.h"

void	null_command2(t_minishell *mini, int n)
{
	int	i;

	i = 0;
	if (dup2(mini->s_cmd->pipe[0], STDIN_FILENO) == -1)
		message_perror("Impossible to read in the pipe");
	manual_redirection(mini, n);
	clear_s_cmd(mini->s_cmd);
}

int exec_buildin2_pipe(t_minishell *mini, int n)
{
	return (0);
}

void	exec_buildin2(t_minishell *mini, int n)
{
	int	i;

	i = 0;
	if (dup2(mini->s_cmd->pipe[0], STDIN_FILENO) == -1)
		message_perror("Impossible to read in the pipe");
	if (n < mini->cmd_n)
	{
		if (dup2(mini->s_cmd->pipe[1], STDOUT_FILENO) == -1)
			message_perror("Impossible to write in the pipe");
	}
	else if (n == mini->cmd_n && mini->cmd_n != 1)
	{
		if (dup2(mini->s_cmd->fd_stdout, STDOUT_FILENO) == -1)
			message_perror("Impossible to write in the pipe");
	}
	close(mini->s_cmd->pipe[0]);
	close(mini->s_cmd->pipe[1]);
	while (i < mini->token_count && mini->token[i].cmd_n != n)
		i++;
	manual_redirection_loop(mini, n, i);
	execute_buildin(mini);
	clear_s_cmd(mini->s_cmd);
}

void	exec_bash_cmd(t_minishell *mini, int n)
{
	int	i;

	i = 0;
	while(mini->s_cmd->pids[i] != 0 && i < mini->cmd_n)
		i++;
	mini->s_cmd->pids[i] = fork();
	if (mini->s_cmd->pids[i] < 0)
	{
		message_perror("Crash in the fork function");
		clear_s_cmd(mini->s_cmd);
	}
	else if (mini->s_cmd->pids[i] == 0)
		child2(mini, n);
	else
	{
		parent2(mini);
		clear_s_cmd(mini->s_cmd);
	}
}
