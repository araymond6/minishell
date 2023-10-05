#include "../include/minishell.h"

//parse the command for the command part, and redirections part 
int	parsing_command(t_minishell *mini, int i)
{
	int		j;

	j = 0;
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
	mini->s_cmd->nredir = redir_count(mini->cmd[i]);
	while (mini->cmd[i][j] && mini->cmd[i])
	{
		j = count_quote(mini->cmd[i], j);
		if (mini->cmd[i][j] == '<')
			j = entry_redirection(mini, i, j + 1);
		else if (mini->cmd[i][j] == '>')
			j = exit_redirection(mini, i, j + 1);
		else if (mini->cmd[i][j] == ' ')
			j++;
		else if(mini->cmd[i][j] == '\"' || mini->cmd[i][j] == '\'')
			j = check_command(mini, i, j);
		else
			j = check_command(mini, i, j);
	}
	return (0);
}

// create the s_cmd list 
int	create_list(t_minishell *mini)
{
	int		i;
	t_cmd	*copy;

	i = 0;
	copy = ft_calloc(1, sizeof(t_cmd));
	if (copy == NULL)
		return (1);
	while (mini->cmd[i] != NULL)
	{
		if (parsing_command(mini, i) == 1)
			return (free_scmd(mini->s_cmd), 1);
		copy = mini->s_cmd;
		mini->s_cmd = mini->s_cmd->next;
		mini->s_cmd->prev = copy;
		i++;
	}
	while (i-- > 0)
		mini->s_cmd = mini->s_cmd->prev;
	return (0);
}
