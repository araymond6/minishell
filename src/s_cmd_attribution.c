#include "../include/minishell.h"

//initialize s_cmd
void	initialize_s_cmd(t_minishell *mini)
{
	int n;
	int pipes[2];

	n = 0;
	mini->s_cmd->path = NULL;
	mini->s_cmd->cmd_arg = NULL;
	mini->s_cmd->pids = ft_calloc(mini->nb_c, sizeof(pid_t));
	mini->s_cmd->pipe = ft_calloc(2 * (mini->nb_c), sizeof(int));
	while(n < mini->nb_c)
	{
		if (pipe(pipes) == -1)
			return (free_scmd(mini->s_cmd), message_perror("Pipe"));
		mini->s_cmd->pipe[2 * n] = pipes[0];
		mini->s_cmd->pipe[(2 * n) -1] = pipes[1];
		n++;
	}
	mini->s_cmd->narg = 0;
	mini->s_cmd->status = 0;
	mini->s_cmd->fd_stdin_out[0] == 0;
	mini->s_cmd->fd_stdin_out[1] == 0;
	mini->s_cmd->pids[0] = 1
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
