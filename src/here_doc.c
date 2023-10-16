#include "../include/minishell.h"

// sets flag for heredoc behaviour
int	set_flag(t_minishell *mini) //TODO: shorten function, start substitution
{
	int	i;
	int	j;
	int test;

	i = 0;
	mini->heredoc_flag = ft_calloc(mini->heredoc_count + 1, sizeof(char));
	if (!mini->heredoc_flag)
		return (1);
	mini->heredoc_count = 0;
	while (mini->cmd[i])
	{
		j = 0;
		while(mini->cmd[i][j])
		{
			if (mini->cmd[i][j] == '<')
			{
				j++;
				if (mini->cmd[i][j] == '<')
				{
					j++;
					if (mini->cmd[i][j] == ' ' || mini->cmd[i][j] == '\t')
						j++;
					while (mini->cmd[i][j] != ' ' && mini->cmd[i][j])
					{
						if (mini->cmd[i][j] == '\'' || mini->cmd[i][j] == '\"')
							mini->heredoc_flag[mini->heredoc_count] = 1;
						j++;
					}
					mini->heredoc_count++;
				}
			}
			else
				j++;
		}
		i++;
	}
	return (0);
}

void	all_here_doc(t_minishell *mini)
{
	int		f;
	t_cmd	*cmd2;

	f = 0;
	cmd2 = mini->s_cmd;
	while (cmd2->cmd)
	{
		if (cmd2->file)
		{
			while (cmd2->file[f])
			{
				if (cmd2->redir[f] == '2')
					here_doc(cmd2->file[f]);
				f++;
			}
		}
		f = 0;
		cmd2 = cmd2->next;
	}
}

// function who read the entry and put it in the here_doc file
int	read_write(char *delimiter, int fd)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = readline("\033[92mHERE_DOC > % \033[0m");
	if (!new_line)
		return (close(fd), message_perror("2.1"));
	//TODO: substitution
	if (ft_strncmp(delimiter, new_line, (ft_strlen(delimiter) + 1)) == 0)
		i = 1;
	else
	{
		write(fd, new_line, ft_strlen(new_line));
		write(fd, "\n", 1);
	}
	free(new_line);
	return (i);
}

// function for the << redirection
int	here_doc(char *delimiter)
{
	int		fd;
	int		i;

	i = 0;
	fd = open("here_doc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (close(fd), message_perror("2"));
	while (i == 0)
		i = read_write(delimiter, fd);
	close(fd);
	return (0);
}
