#include "../include/minishell.h"

static int	check_heredoc(t_minishell *mini)
{
	int	j;

	j = 0;
	if (mini->s_cmd->redir)
	{
		while (mini->s_cmd->redir[j])
		{
			if (mini->s_cmd->redir[j] == '2')
				mini->heredoc_count++;
			j++;
		}
		if (set_flag(mini))
			return (1);
	}
	return (0);
}

int	calloc_node(t_minishell *mini)
{
	if (!mini->s_cmd)
	{
		mini->s_cmd = ft_calloc(1, sizeof(t_cmd));
		if (mini->s_cmd == NULL)
			return (free_scmd(mini->s_cmd), 1);
		initialize_s_cmd(mini->s_cmd);
	}
	if (!mini->s_cmd->next)
	{
		mini->s_cmd->next = ft_calloc(1, sizeof(t_cmd));
		if (mini->s_cmd->next == NULL)
			return (free_scmd(mini->s_cmd), 1);
		initialize_s_cmd(mini->s_cmd->next);
	}
	return (0);
}

//parse the command for the command part, and redirections part 
int	parsing_command(t_minishell *mini, int i)
{
	int		j;

	j = 0;
	if (calloc_node(mini) == 1)
		return (1);
	mini->s_cmd->nredir = redir_count(mini, mini->cmd[i]);
	while (mini->cmd[i][j] && mini->cmd[i])
	{
		if (mini->cmd[i][j] == '<' || mini->cmd[i][j] == '>')
			j = select_redirection(mini, i, j + 1);
		else if (mini->cmd[i][j] == ' ')
			j++;
		else
			j = check_command(mini, i, j);
		if (j == 1)
			return (1);
	}
	return (0);
}

int	create_list(t_minishell *mini)
{
	int		i;
	t_cmd	*copy;

	i = 0;
	while (mini->cmd[i] != NULL)
	{
		if (parsing_command(mini, i) == 1)
			return (free_scmd(mini->s_cmd), 1);
		copy = mini->s_cmd;
		mini->s_cmd = mini->s_cmd->next;
		mini->s_cmd->prev = copy; //TODO: do we need to free copy or nah?
		i++;
	}
	while (i-- > 0)
		mini->s_cmd = mini->s_cmd->prev;
	if (check_heredoc(mini) == 1)
		return (1);
	return (0);
}

int	check_command(t_minishell *mini, int i, int j)
{
	int	k;

	k = 1;
	j = s_cmd_cmd(mini, i, j);
	if (find_path(mini) == -1)
		return (-1);
	mini->s_cmd->narg = nbr_arg(mini, i, j);
	mini->s_cmd->cmd_arg = ft_calloc(mini->s_cmd->narg + 2, sizeof(char *));
	if (!mini->s_cmd->cmd_arg)
		return (-1);
	if (s_cmd_arg_cmd_first(mini) == -1)
		return (-1);
	if (mini->s_cmd->narg > 0)
	{
		while (k < mini->s_cmd->narg)
		{
			j = s_cmd_arg_cmd_middle(mini, i, j, k);
			if (j == -1)
				return (-1);
			k++;
		}
		j = s_cmd_arg_cmd_end(mini, i, j, k);
	}
	return (j);
}
