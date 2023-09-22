/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:12 by araymond          #+#    #+#             */
/*   Updated: 2023/09/22 14:27:34 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static void	special_char_check(t_minishell *mini, int *i)
{
	if (mini->arg[*i] == '\'')
		quote_parse(mini, i);
	else if (mini->arg[*i] == '\"')
		doublequote_parse(mini, i);
	else if (mini->arg[*i] == '$')
		count_sub_dollar(mini, i);
	else if (mini->arg[*i] == '|')
	{
		mini->cmd[mini->parse.c] = calloc((*i + mini->parse.sub + 1), sizeof(char));
		mini->parse.end_block = *i - 1;
		get_block(mini);
		mini->parse.start_block = *i + 1;
		mini->parse.sub = 0;
		mini->parse.c++;
	}
	else if (mini->arg[*i] == ' ' || mini->arg[*i] == '\t' || mini->arg[*i] == '\n')
	{
		(*i)++;
		while (mini->arg[*i] == ' ' || mini->arg[*i] == '\t' || mini->arg[*i] == '\n')
		{
			(*i)++;
			mini->parse.sub--;
		}
		(*i)--;
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
static void	allocate_cmd(t_minishell *mini)
{
	int	i;

	i = 0;
	mini->cmd = calloc((mini->parse.block_count + 1), sizeof(char *));
	if (!mini->cmd)
		malloc_error(mini);
	while (mini->arg[i])
	{
		special_char_check(mini, &i);
		i++;
	}
	mini->cmd[mini->parse.c] = calloc((i + mini->parse.sub + 2), sizeof(char)); // FINISH THIS PART FIRST
	mini->parse.end_block = i;
	get_block(mini);
}

static void trim_cmd(t_minishell *mini)
{
	int		i;
	char	*temp;

	i = -1;
	while (mini->cmd[++i])
	{
		temp = mini->cmd[i];
		mini->cmd[i] = ft_strtrim(mini->cmd[i], " ");
		if (!mini->cmd[i])
			malloc_error(mini);
		free(temp);
	}
}

static void	parse(t_minishell *mini)
{
	char	*arg;
	
	arg = ft_strtrim(mini->arg, " ");
	if (!arg)
	{
		free(mini->arg);
		malloc_error(mini);
	}
	free(mini->arg);
	mini->arg = arg;
	if (!count_blocks(mini))
		return ;
	allocate_cmd(mini);
	trim_cmd(mini);
}

// reads user input w/ readline
void	read_input(t_minishell *mini)
{
	while(1)
	{
		mini->arg = readline("\033[92mminishell % \033[0m");
		if (mini->arg == NULL)
			break ;
		add_history(mini->arg);
		parse(mini);
		x_comm(mini);
		clear_mini(mini);
		free(mini->arg);
	}
}
