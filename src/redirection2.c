#include "../include/minishell.h"

//assign the number for the redirection and the name of the file
int	redirection(t_minishell *mini, int i, int j, char c)
{
	int	r;

	r = 0;
	if (file_n_redir_calloc(mini, c) == 1)
		return (1);
	if (mini->cmd[i][j] == ' ')
		j++;
	while (mini->s_cmd->file[r])
		r++;
	mini->s_cmd->qlen = count_quote(mini->cmd[i], j);
	mini->s_cmd->qlen = mini->s_cmd->qlen - j + 1;
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

int	count_quote2(char *cmd, int i)
{
	while (cmd[i] != ' ' && cmd[i] != '<' && cmd[i] != '>' && cmd[i])
	{
		while (cmd[i] != '\"' && cmd[i] != '\'' && cmd[i] != ' ' && \
		cmd[i] != '<' && cmd[i] != '>' && cmd[i])
			i++;
		i = quote_jump(cmd, i, '\"');
		i = quote_jump(cmd, i, '\'');
	}
	return (i);
}

int	count_quote(char *cmd, int i)
{
	while (cmd[i] != ' ' && cmd[i])
	{
		while (cmd[i] != '\"' && cmd[i] != '\'' && cmd[i] != ' ' && cmd[i])
			i++;
		i = quote_jump(cmd, i, '\"');
		i = quote_jump(cmd, i, '\'');
	}
	return (i);
}
