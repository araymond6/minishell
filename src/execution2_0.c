#include "../include/minishell.h"

void	null_command2(t_minishell *mini, int n)
{
	int i;

	i = 0;
	manual_redirection(mini, n);
	clear_s_cmd(mini->s_cmd);//
}

void exec_buildin2(t_minishell *mini, int n)
{
	int i;

	i = 0;
	manual_redirection(mini, n);
	execute_buildin(mini);
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
		parent2(mini, n);
}