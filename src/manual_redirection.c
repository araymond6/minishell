#include "../include/minishell.h"

void	redirect_input(t_minishell *mini, int i)
{
	int	fd;

	fd = open(mini->token[i].token, O_RDONLY);
	if (fd == -1)
	{
		message_perror(mini->token[i].token);
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		message_perror("Impossible to read in the infile");
	close(fd);
}

void	redirect_here_doc(void)
{
	int	fd;

	fd = open("here_doc.txt", O_RDONLY);
	if (fd == -1)
	{
		message_perror("Here_doc");
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		message_perror("Impossible to read in the infile");
	close(fd);
}

void	redirect_output(t_minishell *mini, int i)
{
	int	fd;

	fd = open(mini->token[i].token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		message_perror(mini->token[i].token);
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		message_perror("Impossible to read in the outfile");
	close(fd);
}

void	redirect_append(t_minishell *mini, int i)
{
	int	fd;

	fd = open(mini->token[i].token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		message_perror(mini->token[i].token);
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		message_perror("Impossible to read in the outfile");
	close(fd);
}
