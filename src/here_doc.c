#include "../include/minishell.h"

static void	redir_loop(t_minishell *mini, int i)
{
	int j;

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
}

// sets flags for heredoc behaviour
int	set_flag(t_minishell *mini)
{
	int	i;

	i = 0;
	mini->heredoc_flag = ft_calloc(mini->heredoc_count + 1, sizeof(char));
	if (!mini->heredoc_flag)
		return (1);
	mini->heredoc_count = 0;
	while (mini->cmd[i])
	{
		redir_loop(mini, i);
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
	mini->heredoc_count = 0;
	while (cmd2)
	{
		if (cmd2->file)
		{
			while (cmd2->file[f])
			{
				if (cmd2->redir[f] == '2')
				{
					here_doc(mini, cmd2->file[f]);
				}
				f++;
			}
			mini->heredoc_count++;
		}
		f = 0;
		cmd2 = cmd2->next;
	}
}

static int	read_write(t_minishell *mini, char *delimiter, int fd) //TODO: Make this cleaner cause wtf me
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = readline("\033[92mHERE_DOC > % \033[0m");
	if (!new_line)
		return (close(fd), message_perror("2.1"));
	if (mini->heredoc_flag[mini->heredoc_count] == 0)
	{
		new_line = heredoc_count(mini, new_line);
		if (!new_line)
		{
			mini->arg = NULL;
			return (1);
		}
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
