#include "../include/minishell.h"

int	all_here_doc2(t_minishell *mini)
{
	int		i;
	pid_t	pidhd;
	int		status;

	i = 0;
	mini->in_heredoc = 1;
	minishell(mini); //TODO: make heredoc signals the way ele-sage does it
	signal_heredoc(mini);
	mini->heredoc_count = 0;
	while (i < mini->token_count)
	{
		if (mini->token[i].type == HERE_DOC)
		{
			pidhd = fork();
			if (pidhd < 0)
				return (free_scmd(mini->s_cmd), 1);
			else if (pidhd == 0)
			{
				i++;
				here_doc(mini, mini->token[i].token);
				free_scmd(mini->s_cmd);
				clear_mini(mini);
			}
			else
			{
				i++;
				mini->heredoc_count++;
				waitpid(pidhd, &status, 0);
				mini->exit_code = status;
				if (mini->exit_code != 0)
					return (free_scmd(mini->s_cmd), 1);
			}
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
	new_line = readline("HERE_DOC > % ");
	if (!new_line)
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
