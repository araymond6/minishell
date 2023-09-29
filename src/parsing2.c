/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:24:44 by araymond          #+#    #+#             */
/*   Updated: 2023/09/29 10:49:37 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	special_check(t_minishell *mini, int *i, int *j, int *spec)
{
	if (mini->arg[*i] == '\'')
		quote_cmd(mini, i, j);
	else if (mini->arg[*i] == '\"')
		doublequote_cmd(mini, i, j);
	else if (mini->arg[*i] == '$')
	{
		sub_dollar(mini, i, j);
		*spec = 1;
	}
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
	return (0);
}

void	get_block(t_minishell *mini)
{
	int	i;
	int	j;
	int	spec;

	spec = 0;
	i = mini->parse.start_block;
	j = 0;
	while (i <= mini->parse.end_block)
	{
		if (special_check(mini, &i, &j, &spec))
			return ;
		if (spec == 0)
			mini->cmd[mini->parse.c][j++] = mini->arg[i++];
		spec = 0;
	}
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

static void	pipe_parse(t_minishell *mini, int *i)
{
	mini->cmd[mini->parse.c] = \
	ft_calloc((*i + mini->parse.sub + 1), sizeof(char));
	if (!mini->cmd[mini->parse.c])
		malloc_error(mini);
	mini->parse.end_block = *i - 1;
	get_block(mini);
	mini->parse.start_block = *i + 1;
	mini->parse.sub = 0;
	mini->parse.c++;
}

void	special_char_check(t_minishell *mini, int *i)
{
	if (mini->arg[*i] == '\'')
		quote_parse(mini, i);
	else if (mini->arg[*i] == '\"')
		doublequote_parse(mini, i);
	else if (mini->arg[*i] == '$')
		count_sub_dollar(mini, i);
	else if (mini->arg[*i] == '|')
		pipe_parse(mini, i);
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
}
