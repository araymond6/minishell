#include "../include/minishell.h"

//initialize s_cmd
void	initialize_s_cmd(t_cmd *cmd)
{
	cmd->redir = NULL;
	cmd->cmd = NULL;
	cmd->path = NULL;
	cmd->cmd_arg = NULL;
	cmd->file = NULL;
	cmd->next = NULL;
	cmd->nredir = 0;
	cmd->prev = NULL;
	cmd->redir = NULL;
	cmd->narg = 0;
	cmd->status = 0;
	cmd->c = 0;
}

int	s_cmd_cmd(t_minishell *mini, int i, int j)
{
	int	r;

	r = 0;
	if (mini->cmd[i][j] == '\'' || mini->cmd[i][j] == '\"')
		mini->s_cmd->qlen = count_quote(mini->cmd[i], j) - j - 1;
	else
		mini->s_cmd->qlen = len_until_space(mini, i, j);
	mini->s_cmd->cmd = ft_calloc(mini->s_cmd->qlen + 1, sizeof(char));
	if (!mini->s_cmd->cmd)
		return (free_scmd(mini->s_cmd), 1);
	while (mini->cmd[i][j] != ' ' && mini->cmd[i][j] != '\t' && mini->cmd[i][j])
	{
		while (mini->cmd[i][j] != '\"' && mini->cmd[i][j] != '\'' && \
			mini->cmd[i][j] != ' ' && mini->cmd[i][j] != '\t' && mini->cmd[i][j])
			mini->s_cmd->cmd[r++] = mini->cmd[i][j++];
		if (mini->cmd[i][j] == '\"')
		{
			j++;
			while (mini->cmd[i][j] != '\"')
				mini->s_cmd->cmd[r++] = mini->cmd[i][j++];
			j++;
		}
		if (mini->cmd[i][j] == '\'')
		{
			j++;
			while (mini->cmd[i][j] != '\'')
				mini->s_cmd->cmd[r++] = mini->cmd[i][j++];
			j++;
		}
	}
	if (mini->cmd[i][j] == ' ' || mini->cmd[i][j] == '\t')
		j++;
	return (j);
}

int	s_cmd_arg_cmd_first(t_minishell *mini)
{
	int	len;

	len = ft_strlen(mini->s_cmd->path);
	mini->s_cmd->cmd_arg[0] = ft_calloc(len + 1, sizeof(char));
	if (!mini->s_cmd->cmd_arg[0])
		return (free_scmd(mini->s_cmd), -1);
	ft_strlcpy(mini->s_cmd->cmd_arg[0], mini->s_cmd->path, len + 1);
	return (0);
}

int	s_cmd_arg_cmd_middle(t_minishell *mini, int i, int j, int k)
{
	int	r;

	r = 0;
	mini->s_cmd->qlen = count_quote(mini->cmd[i], j);
	mini->s_cmd->cmd_arg[k] = ft_calloc(mini->s_cmd->qlen + 1, sizeof(char));
	if (!mini->s_cmd->cmd_arg[k])
		return (free_scmd(mini->s_cmd), -1);
	while (mini->cmd[i][j] != ' ' && mini->cmd[i][j])
	{
		while (mini->cmd[i][j] != '\"' && mini->cmd[i][j] != '\'' && \
		mini->cmd[i][j] != ' ' && mini->cmd[i][j] != '\t' && mini->cmd[i][j] != '\t' && mini->cmd[i][j])
			mini->s_cmd->cmd_arg[k][r++] = mini->cmd[i][j++];
		if (mini->cmd[i][j] == '\"')
		{
			j++;
			while (mini->cmd[i][j] != '\"')
				mini->s_cmd->cmd_arg[k][r++] = mini->cmd[i][j++];
			j++;
		}
		if (mini->cmd[i][j] == '\'')
		{
			j++;
			while (mini->cmd[i][j] != '\'')
				mini->s_cmd->cmd_arg[k][r++] = mini->cmd[i][j++];
			j++;
		}
	}
	if (mini->cmd[i][j] == ' ' || mini->cmd[i][j] == '\t')
		j++;
	return (j);
}

int	s_cmd_arg_cmd_end(t_minishell *mini, int i, int j, int k)
{
	int	r;

	r = 0;
	mini->s_cmd->qlen = count_quote2(mini->cmd[i], j);
	mini->s_cmd->cmd_arg[k] = ft_calloc(mini->s_cmd->qlen + 1, sizeof(char));
	if (!mini->s_cmd->cmd_arg[k])
		return (free_scmd(mini->s_cmd), -1);
	while (mini->cmd[i][j] != ' ' && mini->cmd[i][j] != '\t' && mini->cmd[i][j] != '<' && \
	mini->cmd[i][j] != '>' && mini->cmd[i][j])
	{
		while (mini->cmd[i][j] != '\"' && mini->cmd[i][j] != '\'' \
		&& mini->cmd[i][j] != ' ' && mini->cmd[i][j] != '\t' && mini->cmd[i][j] != '<' && \
		mini->cmd[i][j] != '>' && mini->cmd[i][j])
			mini->s_cmd->cmd_arg[k][r++] = mini->cmd[i][j++];
		if (mini->cmd[i][j] == '\"')
		{
			j++;
			while (mini->cmd[i][j] != '\"')
				mini->s_cmd->cmd_arg[k][r++] = mini->cmd[i][j++];
			j++;
		}
		if (mini->cmd[i][j] == '\'')
		{
			j++;
			while (mini->cmd[i][j] != '\'')
				mini->s_cmd->cmd_arg[k][r++] = mini->cmd[i][j++];
			j++;
		}
	}
	if (mini->cmd[i][j] == ' ' || mini->cmd[i][j] == '\t')
		j++;
	return (j);
}
