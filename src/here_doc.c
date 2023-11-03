#include "../include/minishell.h"

int	all_here_doc2(t_minishell *mini)
{
	int		i;

	i = 0;
	mini->heredoc_count = 0;
	while (i < mini->token_count)
	{
		if (mini->token[i].type == HERE_DOC && mini->sigint == 0)
		{
			i++;
			here_doc(mini, mini->token[i].token);
			mini->heredoc_count++;
			signal_reset(mini);
		}
		i++;
	}
	return (0);
}

static void	redir_loop(t_minishell *mini)
{
	int	i;

	i = 0;
	while (i < mini->token_count)
	{
		if (mini->token[i].type == HERE_DOC)
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
	mini->heredoc_flag = ft_calloc(count_heredoc(mini) + 1, sizeof(char));
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

	i = 0;
	minishell(mini);
	new_line = readline("HERE_DOC > % ");
	if (!new_line || minishell(NULL)->sigint == 1)
		return (close(fd), 1);
	if (mini->heredoc_flag[mini->heredoc_count] == 0 && \
		ft_strncmp(delimiter, new_line, ft_strlen(delimiter) + 1) != 0)
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

char	*create_here_doc_name(int count)
{
	char	*file_name;
	char	*new_file_name;

	file_name = ft_itoa(count);
	if (!file_name)
		return (printf("Impossible to execute here_doc"), NULL);
	new_file_name = ft_strjoin(file_name, "..txt");
	if (!new_file_name)
		return (printf("Impossible to execute here_doc"), NULL);
	free(file_name);
	return (new_file_name);
}

// function for the << redirection
int	here_doc(t_minishell *mini, char *delimiter)
{
	int		fd;
	int		i;
	char	*new_file_name;

	set_signal_for_heredoc(mini);
	i = 0;
	new_file_name = create_here_doc_name(mini->heredoc_count);
	if (!new_file_name)
		return (1);
	fd = open(new_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(new_file_name);
	if (fd == -1)
		return (close(fd), message_perror("Impossible to execute here_doc"));
	while (i == 0)
		i = read_write(mini, delimiter, fd);
	close(fd);
	return (0);
}
