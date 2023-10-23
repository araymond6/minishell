#include "../include/minishell.h"

void redirect_input(t_minishell *mini, int i)
{
	int fd;

	fd = open(mini->token[i].token, O_RDONLY);
	if (fd == -1)
	{
		message_perror(mini->token[i].token);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}
void redirect_here_doc(void)
{
	int fd;

	fd = open("here_doc.txt", O_RDONLY);
	if (fd == -1)
	{
		message_perror("Here_doc");
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}
void redirect_output(t_minishell *mini, int i)
{
	int fd;

	fd = open(mini->token[i].token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		message_perror(mini->token[i].token);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
void redirect_append(t_minishell *mini, int i)
{
	int fd;

	fd = open(mini->token[i].token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		message_perror(mini->token[i].token);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	manual_redirection(t_minishell *mini, int n)
{
	int i;

	i = 0;
	while (i < mini->token_count && mini->token[i].no_cmd != n)
		i++;
	while (i < mini->token_count && mini->token[i].no_cmd == n)
	{
		if (mini->token[i].type == REDIRECT_INPUT)
			redirect_input(mini, ++i);
		else if (mini->token[i].type == HERE_DOC)
		{
			i++;
			redirect_here_doc();
		}
		else if (mini->token[i].type == REDIRECT_OUTPUT)
			redirect_output(mini, ++i);
		else if (mini->token[i].type == APPEND)
			redirect_append(mini, ++i);
		i++;
	}
}
