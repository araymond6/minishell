#include "../include/minishell.h"

int	redir_parsing(t_minishell *mini)
{
	int	i;
	int	c;
	int	count;

	c = 0;
	while (mini->cmd[c])
	{
		i = 0;
		count = 0;
		while (mini->cmd[c][i])
		{
			if (count > 2)
				return (parsing_error(mini), 1);
			if (mini->cmd[c][i] == '<')
			{
				i++;
				count++;
				if (mini->cmd[c][i] == '>' || !mini->cmd[c][i])
					return (parsing_error(mini), 1);
			}
			else if (mini->cmd[c][i] == '>')
			{
				i++;
				count++;
				if (mini->cmd[c][i] == '<' || !mini->cmd[c][i])
					return (parsing_error(mini), 1);
			}
			else if ((count == 2 || count == 1) && \
			((!ft_isalnum(mini->cmd[c][i]) && mini->cmd[c][i] != ' ' && mini->cmd[c][i] != '\'' && mini->cmd[c][i] != '\"') || !mini->cmd[c][i]))
				return (parsing_error(mini), 1);
			else
			{
				i++;
				count = 0;
			}
		}
		c++;
	}
	return (0);
}
