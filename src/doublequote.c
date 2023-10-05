#include "../include/minishell.h"

//adds everything in double quote to mini->cmd
void	doublequote_cmd(t_minishell *mini, int *i, int *j)
{
	mini->cmd[mini->parse.c][(*j)++] = mini->arg[(*i)++];
	while (mini->arg[*i] && mini->arg[*i] != '\"')
	{
		if (mini->arg[*i] == '$' && mini->arg[*i + 1] != ' ' && mini->arg[*i + 1] != '\0')
			sub_dollar(mini, i, j);
		mini->cmd[mini->parse.c][(*j)++] = mini->arg[(*i)++];
	}
}

// checks if the doublequote ends
int	end_doublequote(t_minishell *mini, int *i)
{
	(*i)++;
	while (mini->arg[*i] && mini->arg[*i] != '\"')
		(*i)++;
	if (mini->arg[*i] != '\"')
		return (1);
	return (0);
}

// basic double quote parsing
void	doublequote_parse(t_minishell *mini, int *i)
{
	(*i)++;
	while (mini->arg[*i] && mini->arg[*i] != '\"')
	{
		if (mini->arg[*i])
			count_sub_dollar(mini, i);
		(*i)++;
	}
}
