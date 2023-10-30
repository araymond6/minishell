#include "../include/minishell.h"

void	null_command2(t_minishell *mini, int n)
{
	int	i;

	i = 0;
	manual_redirection(mini, n);
	clear_s_cmd(mini->s_cmd);
}

void	exec_buildin2(t_minishell *mini, int n)
{
	int	i;
	int	output_append;
	int	input_here_doc;

	i = 0;
	output_append = 0;
	input_here_doc = 0;
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
	while (i < mini->token_count && mini->token[i].cmd_n != n)
		i++;
	manual_redirection_loop(mini, n, i);
	execute_buildin(mini);
	close(mini->s_cmd->pipe[0]);
	close(mini->s_cmd->pipe[1]);
	clear_s_cmd(mini->s_cmd);
}

void	exec_bash_cmd(t_minishell *mini, int n)
{
	set_signal_for_process(mini);
	mini->s_cmd->pids[n - 1] = fork();
	if (mini->s_cmd->pids[n - 1] < 0)
	{
		message_perror("Crash in the fork function");
		clear_s_cmd(mini->s_cmd);
	}
	else if (mini->s_cmd->pids[n - 1] == 0)
		child2(mini, n);
	else
		parent2(mini);
	clear_s_cmd(mini->s_cmd);
}
