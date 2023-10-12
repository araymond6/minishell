#include "../include/minishell.h"

//this function count the nbrs of argument fot command
// ex: ls -l -a => 2 arguments
int	nbr_arg(t_minishell *mini, int i, int j)
{
	int	space;
	int	k;

	space = 0;
	k = 0;
	while (mini->cmd[i][j + k]
		&& mini->cmd[i][j + k] != '>'
		&& mini->cmd[i][j + k] != '<')
	{
		if (mini->cmd[i][j + k] == '\'')
		{
			k++;
			while (mini->cmd[i][j + k] != '\'')
				k++;
		}
		if (mini->cmd[i][j + k] == '\"')
		{
			k++;
			while (mini->cmd[i][j + k] != '\"')
				k++;
		}
		if (mini->cmd[i][j + k] == ' '
			&& mini->cmd[i][j + k + 1] != '>'
			&& mini->cmd[i][j + k + 1] != '<')
			space++;
		k++;
	}
	return (space);
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
