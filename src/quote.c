#include "../include/minishell.h"



void	quote_cmd(t_minishell *mini, int *i, int *j)
{
	mini->cmd[mini->parse.c][(*j)++] = mini->arg[(*i)++];
	while (mini->arg[*i] && mini->arg[*i] != '\'')
		mini->cmd[mini->parse.c][(*j)++] = mini->arg[(*i)++];
}

int	end_quote(t_minishell *mini, int *i)
{
	(*i)++;
	while (mini->arg[*i] && mini->arg[*i] != '\'')
		(*i)++;
	if (mini->arg[*i] != '\'')
		return (1);
	return (0);
}

void	quote_parse(t_minishell *mini, int *i)
{
	(*i)++;
	while (mini->arg[*i] && mini->arg[*i] != '\'')
		(*i)++;
}
