#include "../include/minishell.h"

int	count_quote2(char *cmd, int i)
{
	while (cmd[i] != ' ' && cmd[i] != '<' && cmd[i] != '>' && cmd[i])
	while (cmd[i] != ' ' && cmd[i] != '<' && cmd[i] != '>' && cmd[i])
	{
		while (cmd[i] != '\"' && cmd[i] != '\'' && cmd[i] != ' ' && \
		cmd[i] != '<' && cmd[i] != '>' && cmd[i])
			i++;
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"')
				i++;
			i++;
		}
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'')
				i++;
			i++;
		}
	}
	return (i);
}

int	count_quote(char *cmd, int i)
{
	while (cmd[i] != ' ' && cmd[i])
	{
		while (cmd[i] != '\"' && cmd[i] != '\'' && cmd[i] != ' ' && cmd[i])
			i++;
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"')
				i++;
			i++;
		}
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'')
				i++;
			i++;
		}
	}
	return (i);
}

//count the nbr of redirection in the command line
int	redir_count(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"')
				i++;
		}
		else if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'')
				i++;
		}
		if (cmd[i] == '<')
		{
			count += 1;
			if (cmd[i + 1] == '<')
				i++;
		}
		else if (cmd[i] == '>')
		{
			count += 1;
			if (cmd[i + 1] == '>')
				i++;
		}
		i++;
	}
	return (count);
}

int	redir_quote(t_minishell *mini, int i, int j, int r)
{
	int	index;

	index = 0;
	if (mini->cmd[i][j] == '\"')
	{
		while (mini->cmd[i][++j] != '\"')
			mini->s_cmd->file[r][index++] = mini->cmd[i][j];
		j++;
	}
	else if (mini->cmd[i][j] == '\'')
	{
		while (mini->cmd[i][++j] != '\'')
			mini->s_cmd->file[r][index++] = mini->cmd[i][j];
		j++;
	}
	else
	{
		index = -1;
		while (++index < mini->s_cmd->qlen)
			mini->s_cmd->file[r][index] = mini->cmd[i][j + index];
		j += index;
	}
	return (j);
}

//assign the number for the redirection and the name of the file
int	redirection(t_minishell *mini, int i, int j, char c)
{
	int	r;

	mini->s_cmd->qlen = 0;
	r = 0;
	if (file_n_redir_calloc(mini, c) == 1)
		return (1);
	if (mini->cmd[i][j] == ' ')
		j++;
	if (mini->cmd[i][j] == '\'' || mini->cmd[i][j] == '\"')
		mini->s_cmd->qlen = count_quote(mini->cmd[i], j) - j - 1;
	else 
		mini->s_cmd->qlen = len_until_space(mini, i, j);
	while (mini->s_cmd->file[r])
		r++;
	mini->s_cmd->file[r] = ft_calloc(mini->s_cmd->qlen + 1, sizeof(char));
	if (!mini->s_cmd->file[r])
		return (free_scmd(mini->s_cmd), 1);
	return (redir_quote(mini, i, j, r));
}

int	select_redirection(t_minishell *mini, int i, int j)
{
	if (mini->cmd[i][j] == '<')
		j = redirection(mini, i, j + 1, '2');
	else if (mini->cmd[i][j] == '>')
		j = redirection(mini, i, j + 1, '4');
	else if (mini->cmd[i][j] == ' ' && mini->cmd[i][j - 1] == '<')
		j = redirection(mini, i, j + 1, '1');
	else if (mini->cmd[i][j] == ' ' && mini->cmd[i][j - 1] == '>')
		j = redirection(mini, i, j + 1, '3');
	else if (mini->cmd[i][j - 1] == '<')
		j = redirection(mini, i, j, '1');
	else if (mini->cmd[i][j - 1] == '>')
		j = redirection(mini, i, j, '3');
	return (j);
}
