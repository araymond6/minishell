#include "../include/minishell.h"

int	special_check(t_minishell *mini, int *i, int *j, int *spec)
{
	if (mini->arg[*i] == '\'')
		quote_cmd(mini, i, j);
	else if (mini->arg[*i] == '\"')
		*spec = doublequote_cmd(mini, i, j);
	else if (mini->arg[*i] == '$' && mini->arg[*i + 1] != ' ' \
	&& mini->arg[*i + 1] != '\0')
		*spec = sub_dollar(mini, i, j, mini->cmd[mini->parse.c]);
	else if (mini->arg[*i] == '|')
		return (1);
	else if (mini->arg[*i] == ' ' || mini->arg[*i] == '\t' || \
	mini->arg[*i] == '\n')
	{
		(*i)++;
		while (mini->arg[*i] == ' ' || mini->arg[*i] == '\t' || \
		mini->arg[*i] == '\n')
			(*i)++;
		(*i)--;
	}
	if (*spec == 1)
		return (1);
	return (0);
}

int	get_block(t_minishell *mini)
{
	int	i;
	int	j;
	int	spec;

	spec = 0;
	i = mini->parse.start_block;
	j = 0;
	while (i < mini->parse.end_block)
	{
		if (special_check(mini, &i, &j, &spec))
			return (1);
		if (spec == 0)
			mini->cmd[mini->parse.c][j++] = mini->arg[i++];
		spec = 0;
	}
	return (0);
}

int	quote_check(t_minishell *mini, int *i)
{
	if (mini->arg[*i] == '\'')
	{
		if (end_quote(mini, i))
		{
			parsing_error(mini);
			return (0);
		}
	}
	else if (mini->arg[*i] == '\"')
	{
		if (end_doublequote(mini, i))
		{
			parsing_error(mini);
			return (0);
		}
	}
	return (1);
}

static int	pipe_parse(t_minishell *mini, int *i)
{
	if (spacentabs_check(&mini->arg[*i + 1]))
		return (parsing_error(mini), 1);
	mini->cmd[mini->parse.c] = \
	ft_calloc((*i + mini->parse.sub + 1), sizeof(char));
	if (!mini->cmd[mini->parse.c])
	{
		mini->cmd[mini->parse.c] = NULL;
		return (malloc_error(mini, mini->cmd), 1);
	}
	mini->parse.end_block = *i - 1;
	if (get_block(mini))
		return (1);
	mini->parse.start_block = *i + 1;
	mini->parse.sub = 0;
	mini->parse.c++;
	return (0);	
}

int	special_char_check(t_minishell *mini, int *i)
{
	int	error;

	error = 0;
	if (mini->arg[*i] == '\'')
		quote_parse(mini, i);
	else if (mini->arg[*i] == '\"')
	{
		if (doublequote_parse(mini, i))
			return (1);
	}
	else if (mini->arg[*i] == '$' && mini->arg[*i + 1] != ' ' \
	&& mini->arg[*i + 1] != '\0')
		error = count_sub_dollar(mini, i);
	else if (mini->arg[*i] == '|')
		error = pipe_parse(mini, i);
	else if (mini->arg[*i] == ' ' || mini->arg[*i] == '\t' || \
	mini->arg[*i] == '\n')
	{
		(*i)++;
		while (mini->arg[*i] == ' ' || mini->arg[*i] == '\t' || \
		mini->arg[*i] == '\n')
		{
			(*i)++;
			mini->parse.sub--;
		}
		(*i)--;
	}
	if (error == 1)
		return (1);
	return (0);
}
