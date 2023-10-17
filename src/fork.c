#include "../include/minishell.h"

int	null_command(t_minishell *mini, int *pids, int n)
{
	int	originalstdout;
	int	originalstdin;
	int	r;

	r = 0;
	originalstdin = dup(STDIN_FILENO);
	originalstdout = dup(STDOUT_FILENO);
	if (mini->s_cmd->prev->cmd != NULL)
		close(mini->s_cmd->prev->fd[0]);
	if (mini->s_cmd->next->cmd == NULL)
		close(mini->s_cmd->fd[0]);
	close(mini->s_cmd->fd[1]);
	if (mini->s_cmd->redir)
	{
		while (mini->s_cmd->redir[r])
		{
			change_inf(mini->s_cmd->redir[r], mini->s_cmd->file[r]);
			change_out(mini->s_cmd->redir[r], mini->s_cmd->file[r]);
			r++;
		}
	}
	if (dup2(originalstdout, STDOUT_FILENO) == -1)
	{
		close(originalstdin);
		close(originalstdout);
		return (message_perror("Error restoring stdout"));
	}
	if (dup2(originalstdin, STDIN_FILENO) == -1)
	{
		close(originalstdin);
		close(originalstdout);
		return (message_perror("Error restoring stdin"));
	}
	close(originalstdin);
	close(originalstdout);
	mini->s_cmd = mini->s_cmd->next;
	forker(n - 1, pids + 1, mini);
	return (0);
}

int	exec_buildin(t_minishell *mini, int *pids, int n)
{
	int	originalstdout;
	int	r;

	r = 0;
	originalstdout = dup(STDOUT_FILENO);
	if (dup2(mini->s_cmd->fd[1], STDOUT_FILENO) == -1)
		return (close(mini->s_cmd->fd[1]), \
			close(mini->s_cmd->fd[0]), EXIT_FAILURE);
	if (mini->s_cmd->redir)
	{
		while (mini->s_cmd->redir[r])
		{
			change_inf(mini->s_cmd->redir[r], mini->s_cmd->file[r]);
			change_out(mini->s_cmd->redir[r], mini->s_cmd->file[r]);
			r++;
		}
	}
	execute_buildin(mini);
	parent(mini->s_cmd);
	if (dup2(originalstdout, STDOUT_FILENO) == -1)
		return (message_perror("Error restoring stdout"));
	close(originalstdout);
	mini->s_cmd = mini->s_cmd->next;
	forker(n - 1, pids + 1, mini);
	return (0);
}

int	last_buildin(t_minishell *mini)
{
	int	originalstdout;
	int	r;

	r = 0;
	originalstdout = dup(STDOUT_FILENO);
	if (mini->s_cmd->redir)
	{
		while (mini->s_cmd->redir[r])
		{
			change_inf(mini->s_cmd->redir[r], mini->s_cmd->file[r]);
			change_out(mini->s_cmd->redir[r], mini->s_cmd->file[r]);
			r++;
		}
	}
	execute_buildin(mini);
	parent(mini->s_cmd);
	if (dup2(originalstdout, STDOUT_FILENO) == -1)
		return (message_perror("Error restoring stdout"));
	close(originalstdout);
	mini->s_cmd = mini->s_cmd->next;
	return (0);
}

int	forker(int n, int *pids, t_minishell *mini)
{
	int	r;

	r = 0;
	if (pipe(mini->s_cmd->fd) == -1)
		return (free_scmd(mini->s_cmd), message_perror("Pipe"));
	if (n > 0)
	{
		if (mini->s_cmd->cmd == NULL)
		{
			if (null_command(mini, pids, n) == 1)
				return (free(pids), 1);
		}
		else if (isbuildin(mini->s_cmd->cmd) == 0 && n > 1)
		{
			if (exec_buildin(mini, pids, n) == 1)
				return (free(pids), 1);
		}
		else if (isbuildin(mini->s_cmd->cmd) == 0 && n == 1)
		{
			if (last_buildin(mini) == 1)
				return (free(pids), 1);
		}
		else
		{
			if (to_fork(mini, pids, n))
				return (free(pids), 1);
		}
	}
	return (0);
}

int	to_fork(t_minishell *mini, int *pids, int n)
{
	*pids = fork();
	if (*pids < 0)
	{
		free(pids);
		return (free_scmd(mini->s_cmd), message_perror("Fork"));
	}
	else if (*pids == 0)
	{
		free(pids);
		child(mini);
	}
	else if (*pids > 0)
	{
		parent(mini->s_cmd);
		mini->s_cmd = mini->s_cmd->next;
		forker(n - 1, pids + 1, mini);
	}
	return (0);
}
