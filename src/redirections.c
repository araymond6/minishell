#include "../include/minishell.h"

int	count_quote(char *cmd, int i)
{
	if (cmd[i] == '\"')
	{
		i++;
		while (cmd[i] != '\"')
			i++;
	}
	if (cmd[i] == '\'')
	{
		i++;
		while (cmd[i] != '\'')
			i++;
	}
	return (i);
}
//count the nbr of redirection in the command line
int	redir_count(char *cmd)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (cmd[++i])
	{
		i = count_quote(cmd, i);
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
	}
	return (count);
}

int	file_n_redir_calloc(t_minishell *mini, int c)
{
	int	k;

	k = 0;
	if (!mini->s_cmd->file)
	{
		mini->s_cmd->file = ft_calloc(mini->s_cmd->nredir + 1, sizeof(char *));
		if (!mini->s_cmd->file)
			return (free_scmd(mini->s_cmd), 1);
	}
	if (!mini->s_cmd->redir)
	{
		mini->s_cmd->redir = ft_calloc(mini->s_cmd->nredir + 1, sizeof(char));
		if (!mini->s_cmd->redir)
			return (free_scmd(mini->s_cmd), 1);
	}
	while (mini->s_cmd->redir[k])
		k++;
	mini->s_cmd->redir[k] = c;
	return (0);
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
		while (++index < mini->s_cmd->quote_len)
			mini->s_cmd->file[r][index] = mini->cmd[i][j + index];
		j += index;
	}
	return (j);
}

//assign the number for the redirection and the name of the file
int	redirection(t_minishell *mini, int i, int j, char c)
{
	int	r;
	int	index;

	mini->s_cmd->quote_len = 0;
	r = 0;
	index = -1;
	if (file_n_redir_calloc(mini, c) == 1)
		return(1);
	if (mini->cmd[i][j] == ' ')
		j++;
	if (mini->cmd[i][j] == '\'' || mini->cmd[i][j] == '\"')
		mini->s_cmd->quote_len =  count_quote(mini->cmd[i], j) - j - 1;
	else 
		mini->s_cmd->quote_len = len_until_space(mini, i, j);
	while (mini->s_cmd->file[r])
		r++;
	mini->s_cmd->file[r] = ft_calloc(mini->s_cmd->quote_len + 1, sizeof(char));
	if(!mini->s_cmd->file[r])
		return(free_scmd(mini->s_cmd), 1);
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
	else if(mini->cmd[i][j - 1] == '<')
		j = redirection(mini, i, j, '1');
	else if (mini->cmd[i][j - 1] == '>')
		j = redirection(mini, i, j, '3');
	return (j);
}

