/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:12 by araymond          #+#    #+#             */
/*   Updated: 2023/09/06 09:27:14 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	quote_check(t_minishell *mini, int *i)
{
	if (mini->arg[*i] == '\'')
	{
		if (!end_quote(mini, i))
		{
			parsing_error(mini);
			return (0);
		}
	}
	else if (mini->arg[*i] == '\"')
	{
		if (!end_doublequote(mini, i))
		{
			parsing_error(mini);
			return (0);
		}
	}
	return (1);
}

int	special_char_check(t_minishell *mini, int *i, int *count)
{
	if (mini->arg[*i] == '\'')
		quote_parse(mini, i);
	else if (mini->arg[*i] == '\"')
		doublequote_parse(mini, i);
	else if (mini->arg[*i] == '$')
		count_sub_dollar(mini, i);
	else if (mini->arg[*i] == '|')
	{
		mini->cmd[*count] = calloc((*i + mini->parse.sub + 1), sizeof(char));
		get_block(mini, i, count);
		(*count)++;
	}
}

// main parsing func, block++ for amount of char* necessary to malloc.
static int	count_blocks(t_minishell *mini)
{
	int	i;

	i = 0;
	while (mini->arg[i])
	{
		if (mini->arg[i] == '\'' || mini->arg[i] == '\"')
		{
			if (!quote_check(mini, &i))
				return (0);
		}
		else if (mini->arg[i] == '|')
			mini->parse.block_count++;
		i++;
	}
	mini->parse.block_count++;
	return (1);
}

// mallocs char*s the necessary amount of char
static int	allocate_cmd(t_minishell *mini)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	mini->cmd = calloc((mini->parse.block_count + 1), sizeof(char *));
	if (!mini->cmd)
		malloc_error(mini);
	while (mini->arg[i])
	{
		if (!special_char_check(mini, &i, &count))
			return (1);
		i++;
	}
	return (1);
}

static void	parse(t_minishell *mini)
{
	if (!count_blocks(mini))
		return ;
	if (!allocate_cmd(mini))
		return ;
}

// reads user input w/ readline
int	read_input(t_minishell *mini)
{
	while(1)
	{
		mini->arg = readline("\033[92mminishell % \033[0m");
		if (mini->arg == NULL)
			break ;
		add_history(mini->arg);
		parse(mini);
		free(mini->arg);
	}
}
