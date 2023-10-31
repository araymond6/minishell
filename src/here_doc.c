#include "../include/minishell.h"

void	all_here_doc2(t_minishell *mini)
{
	int	i;

	i = 0;
	mini->heredoc_count = 0;
	while (i < mini->token_count)
	{
		if (mini->token[i].type == HERE_DOC)
		{
			i++;
			here_doc(mini, mini->token[i].token);
			mini->heredoc_count++;
		}
		i++;
	}
}

static void	redir_loop(t_minishell *mini)
{
	int	i;

	i = 0;
	while (i < mini->token_count)
	{
		if (mini->token[i].type == HERE_DOC) // TODO: heredoc flags to test
		{
			if (mini->token[i + 1].inquote == 1)
				mini->heredoc_flag[mini->heredoc_count++] = 1;
			else
				mini->heredoc_count++;
		}
		i++;
	}
}

// sets flags for heredoc behaviour
int	set_heredoc_flag(t_minishell *mini)
{
	int	i;

	i = 0;
	mini->heredoc_flag = ft_calloc(mini->heredoc_count + 1, sizeof(char));
	if (!mini->heredoc_flag)
		return (1);
	mini->heredoc_count = 0;
	redir_loop(mini);
	return (0);
}

static int	read_write(t_minishell *mini, char *delimiter, int fd)
{
	char	*new_line;
	int		i;

	(void) mini;
	i = 0;
	new_line = readline("\033[92mHERE_DOC > % \033[0m");
	if (!new_line)
		return (close(fd), message_perror("2.1"));
	if (mini->heredoc_flag[mini->heredoc_count] == 0)
	{
		new_line = heredoc_substitution(mini, new_line);
		if (!new_line)
			return (1);
	}
	if (ft_strncmp(delimiter, new_line, (ft_strlen(delimiter) + 1)) == 0)
		i = 1;
	else
	{
		write(fd, new_line, ft_strlen(new_line));
		write(fd, "\n", 1);
	}
	free(new_line);
	new_line = NULL;
	return (i);
}

// function for the << redirection
int	here_doc(t_minishell *mini, char *delimiter)
{
	int		fd;
	int		i;

	i = 0;
	fd = open("here_doc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (close(fd), message_perror("2"));
	while (i == 0)
		i = read_write(mini, delimiter, fd);
	close(fd);
	return (0);
}
