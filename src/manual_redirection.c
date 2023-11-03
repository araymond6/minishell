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

void	redirect_here_doc(t_minishell *mini, int i)
{
	int		fd;
	int		n;
	char	*new_file_name;

	n = 0;
	mini->heredoc_count = 0;
	while (n < i - 1)
	{
		if (mini->token[n].type == HERE_DOC)
			mini->heredoc_count++;
		n++;
	}
	new_file_name = create_here_doc_name(mini);
	fd = open(new_file_name, O_RDONLY);
	free(new_file_name);
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
