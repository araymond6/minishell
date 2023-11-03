#include "../include/minishell.h"

void	manual_redirection_loop(t_minishell *mini, int n, int i)
{
	while (i < mini->token_count && mini->token[i].cmd_n == n)
	{
		if (mini->token[i].type == REDIRECT_INPUT)
			redirect_input(mini, ++i);
		else if (mini->token[i].type == HERE_DOC)
			redirect_here_doc(mini, ++i);
		else if (mini->token[i].type == REDIRECT_OUTPUT)
			redirect_output(mini, ++i);
		else if (mini->token[i].type == APPEND)
			redirect_append(mini, ++i);
		i++;
	}
}

void	manual_redirection(t_minishell *mini, int n)
{
	int	i;

	i = 0;
	if (n < mini->cmd_n)
	{
		if (dup2(mini->s_cmd->pipe[1], STDOUT_FILENO) == -1)
			message_perror("Impossible to write in the pipe");
		close(mini->s_cmd->pipe[1]);
	}
	else if (n == mini->cmd_n && mini->cmd_n != 1)
	{
		if (dup2(mini->s_cmd->fd_stdout, STDOUT_FILENO) == -1)
			message_perror("Impossible to write in the pipe");
		close(mini->s_cmd->pipe[1]);
	}
	else
		close(mini->s_cmd->pipe[1]);
	close(mini->s_cmd->pipe[0]);
	while (i < mini->token_count && mini->token[i].cmd_n != n)
		i++;
	manual_redirection_loop(mini, n, i);
}

void	redirect_the_output(t_minishell *mini, int n)
{
	if (n < mini->cmd_n)
	{
		if (dup2(mini->s_cmd->pipe[1], STDOUT_FILENO) == -1)
			message_perror("Impossible to write in the pipe");
		close(mini->s_cmd->pipe[1]);
	}
	else if (n == mini->cmd_n && mini->cmd_n != 1)
	{
		if (dup2(mini->s_cmd->fd_stdout, STDOUT_FILENO) == -1)
			message_perror("Impossible to write in the pipe");
		close(mini->s_cmd->pipe[1]);
	}
}
