#include "../include/minishell.h"

int	forker(int n, int *pids, t_minishell *mini)
{
	int	i;
	int	originalstdout;

	i = 0;
	clear_mini(mini);
	if (pipe(mini->s_cmd->fd) == -1)
		return (free_scmd(mini->s_cmd), message_perror("Pipe"));
	if (n > 0)
	{
		if (mini->s_cmd->cmd == NULL)
		{
			parent(mini->s_cmd);
			mini->s_cmd = mini->s_cmd->next;
			forker(n - 1, pids +1, mini);
		}
		else if (isbuildin(mini->s_cmd->cmd) == 0 && n > 1)
		{
			originalstdout = dup(STDOUT_FILENO);
			if (dup2(mini->s_cmd->fd[1], STDOUT_FILENO) == -1)
				return (close(mini->s_cmd->fd[1]), close(mini->s_cmd->fd[0]), EXIT_FAILURE);
			execute_buildin(mini);
			parent(mini->s_cmd);
			if (dup2(originalstdout, STDOUT_FILENO) == -1)
				return (message_perror("Error restoring stdout"));
			close(originalstdout);
			mini->s_cmd = mini->s_cmd->next;
			forker(n - 1, pids +1, mini);
		}
		else if (isbuildin(mini->s_cmd->cmd) == 0 && n == 1)
		{
			execute_buildin(mini);
			parent(mini->s_cmd);
			mini->s_cmd = mini->s_cmd->next;
		}
		else
			if (to_fork(mini, pids, i, n))
				return (1);
	}
	return (0);
}

int	to_fork(t_minishell *mini, int *pids, int i, int n)
{
	pids[i] = fork();
	if (pids[i] < 0)
		return (free_scmd(mini->s_cmd), message_perror("Fork"));
	else if (pids[i] == 0)
	{
		child(mini);
		mini->s_cmd = mini->s_cmd->next;
	}
	else if (pids[i] > 0)
	{
		parent(mini->s_cmd);
		mini->s_cmd = mini->s_cmd->next;
		forker(n - 1, pids +1, mini);
	}
	return (0);
}