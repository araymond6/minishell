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
	cmd->prev = ft_calloc(1, sizeof(t_cmd));
	cmd->redir = NULL;
	cmd->narg = 0;
	cmd->status = 0;
}

// s_cmd : attribute a value to cmd
int	s_cmd_cmd(t_minishell *mini, int i, int j)
{
	if (mini->cmd[i][j] == '\'' || mini->cmd[i][j] == '\"')
		mini->s_cmd->qlen = count_quote(mini->cmd[i], j) - j - 1;
	else
		mini->s_cmd->qlen = len_until_space(mini, i, j);
	mini->s_cmd->cmd = ft_calloc(mini->s_cmd->qlen + 1, sizeof(char));
	if (!mini->s_cmd->cmd)
		return (free_scmd(mini->s_cmd), -1);
	if (mini->cmd[i][j] == '\'' || mini->cmd[i][j] == '\"')
	{
		j = ft_strjcpy(mini->s_cmd->cmd, mini->cmd[i], mini->s_cmd->qlen, ++j);
		j++;
	}
	else
		j = ft_strjcpy(mini->s_cmd->cmd, mini->cmd[i], mini->s_cmd->qlen, j);
	return (j);
}

// s_cmd : attribute a value to arg_cmd[0]
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

// s_cmd : attribute a value to arg_cmd betwenn arg_cmd[0] and arg_cmd[last]
int	s_cmd_arg_cmd_middle(t_minishell *mini, int i, int j, int k)
{
	int	len;
	int	r;

	r = 0;
	len = 0;
	mini->s_cmd->qlen = count_quote(mini->cmd[i], j);
	mini->s_cmd->cmd_arg[k] = ft_calloc(mini->s_cmd->qlen + 1, sizeof(char));
	if (!mini->s_cmd->cmd_arg[k])
		return (free_scmd(mini->s_cmd), -1);
	while (mini->cmd[i][j] != ' ' && mini->cmd[i][j])
	while (mini->cmd[i][j] != ' ' && mini->cmd[i][j])
	{
		while (mini->cmd[i][j] != '\"' && mini->cmd[i][j] != '\'' && \
		mini->cmd[i][j] != ' ' && mini->cmd[i][j])
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
	if (mini->cmd[i][j] == ' ')
		j++;
	return (j);
}

// s_cmd : attribute a value to arg_cmd[last]
int	s_cmd_arg_cmd_end(t_minishell *mini, int i, int j, int k)
{
	int	len;
	int	r;

	r = 0;
	len = 0;
	mini->s_cmd->qlen = count_quote2(mini->cmd[i], j);
	mini->s_cmd->cmd_arg[k] = ft_calloc(mini->s_cmd->qlen + 1, sizeof(char));
	if (!mini->s_cmd->cmd_arg[k])
		return (free_scmd(mini->s_cmd), -1);
	while (mini->cmd[i][j] != ' ' && mini->cmd[i][j] != '<' && \
	mini->cmd[i][j] != '>' && mini->cmd[i][j])
	{
		while (mini->cmd[i][j] != '\"' && mini->cmd[i][j] != '\'' \
		&& mini->cmd[i][j] != ' ' && mini->cmd[i][j] != '<' && \
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
	if (mini->cmd[i][j] == ' ')
		j++;
	return (j);
}
