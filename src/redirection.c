#include "../include/minishell.h"

int	quote_jump(char *cmd, int i, char c)
{
	if (cmd[i] == c)
	{
		i++;
		while (cmd[i] != c)
			i++;
		i++;
	}
	return (i);
}

int	redirection_jump(t_minishell *mini, char *cmd, int i, char c)
{
	if (cmd[i] == c)
	{
		mini->s_cmd->c += 1;
		if (cmd[i + 1] == c)
			i++;
		i++;
	}
	return (i);
}

//count the nbr of redirection in the command line
int	redir_count(t_minishell *mini, char *cmd)
{
	int	i;
	int	index;

	i = 0;
	mini->s_cmd->c = 0;
	while (cmd[i])
	{
		index = i;
		i = quote_jump(cmd, i, '\"');
		i = quote_jump(cmd, i, '\'');
		i = redirection_jump(mini, cmd, i, '<');
		i = redirection_jump(mini, cmd, i, '>');
		if (index == i)
			i++;
	}
	return (mini->s_cmd->c);
}

int	redir_quote(t_minishell *mini, int i, int j, int r)
{
	int	index;

	index = 0;
	while (mini->cmd[i][j] && mini->cmd[i][j] != ' ')
	{
		if (mini->cmd[i][j] == '\"')
		{
			j++;
			while (mini->cmd[i][j] != '\"')
			{
				mini->s_cmd->file[r][index] = mini->cmd[i][j];
				j++;
				index++;
			}
			j++;
		}
		else if (mini->cmd[i][j] == '\'')
		{
			j++;
			while (mini->cmd[i][j] != '\'')
			{
				mini->s_cmd->file[r][index] = mini->cmd[i][j];
				j++;
				index++;
			}
			j++;
		}
		else
		{
			while (mini->cmd[i][j] != '\'' && mini->cmd[i][j] != '\"'
				&& mini->cmd[i][j] != ' ' && mini->cmd[i][j])
			{
				mini->s_cmd->file[r][index] = mini->cmd[i][j];
				j++;
				index++;
			}
		}
	}
	return (j);
}
