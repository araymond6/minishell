#include "../include/minishell.h"

// child side of the process - make the execution
int	child(t_minishell *mini)
{
	int	i;

	i = -1;
	printf("hi");
	if (mini->s_cmd->prev->cmd != NULL)
		if (dup2(mini->s_cmd->prev->fd[0], STDIN_FILENO) == -1)
			return (close(mini->s_cmd->fd[0]), \
				close(mini->s_cmd->fd[1]), EXIT_FAILURE);
	if (mini->s_cmd->next->cmd != NULL && mini->s_cmd->next)
		if (dup2(mini->s_cmd->fd[1], STDOUT_FILENO) == -1)
			return (close(mini->s_cmd->fd[0]), \
				close(mini->s_cmd->fd[1]), EXIT_FAILURE);
	if (mini->s_cmd->prev->cmd != NULL)
		close(mini->s_cmd->prev->fd[0]);
	if (mini->s_cmd->next->cmd == NULL)
		close(mini->s_cmd->fd[0]);
	close(mini->s_cmd->fd[1]);
	if (mini->s_cmd->redir)
	{
		while (mini->s_cmd->redir[++i])
		{
			change_inf(mini->s_cmd->redir[i], mini->s_cmd->file[i]);
			change_out(mini->s_cmd->redir[i], mini->s_cmd->file[i]);
		}
	}
	return (execute_cmd(mini));
}

int	parent(t_cmd *cmd)
{
	int	originalstdin;

	originalstdin = dup(STDIN_FILENO);
	close(cmd->fd[1]);
	if (cmd->prev->cmd != NULL)
	{
		if (dup2(cmd->prev->fd[0], STDIN_FILENO) == -1)
		{
			close(cmd->fd[0]);
			close(originalstdin);
			exit(EXIT_FAILURE);
		}
	}
	if (cmd->prev->cmd != NULL)
		close(cmd->prev->fd[0]);
	if (cmd->next->cmd == NULL)
		close(cmd->fd[0]);
	if (dup2(originalstdin, STDIN_FILENO) == -1)
		return (message_perror("Error restoring stdin"));
	close(originalstdin);
	return (0);
}
