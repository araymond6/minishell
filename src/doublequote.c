#include "../include/minishell.h"

//adds everything in double quote to mini->cmd
int	doublequote_cmd(t_minishell *mini, int *i, int *j)
{
	mini->cmd[mini->parse.c][(*j)++] = mini->arg[(*i)++];
	while (mini->arg[*i] && mini->arg[*i] != '\"')
	{
		if (mini->arg[*i] == '$' && mini->arg[*i + 1] != ' ' \
		&& mini->arg[*i + 1] != '\0')
		{
			if (sub_dollar(mini, i, j, mini->cmd[mini->parse.c]))
				return (1);
		}
		mini->cmd[mini->parse.c][(*j)++] = mini->arg[(*i)++];
	}
	return (0);
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
int	doublequote_parse(t_minishell *mini, int *i)
{
	(*i)++;
	while (mini->arg[*i] && mini->arg[*i] != '\"')
	{
		if (mini->arg[*i] == '$')
		{
			if (count_sub_dollar(mini, i) == 1)
				return (1);
		}
		if (mini->arg[*i] == '\0')
			return (0);
		(*i)++;
	}
	return (0);
}
