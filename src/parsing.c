/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:12 by araymond          #+#    #+#             */
/*   Updated: 2023/08/29 15:35:51 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sub_dollar(t_minishell *mini, int *i)
{
	
}

// counts how many characters to remove
void	count_sub_dollar(t_minishell *mini, int *i)
{
	(*i)++;
	while ((mini->arg[*i] != ' ' || mini->arg[*i] != '$') && mini->arg[*i])
	{
		if (mini->arg[*i] == '\'')
		{

		}
		else if (mini->arg[*i] == '\"')
		{
			
		}
		(*i)++;
	}
	if (mini->arg[*i] == '$')
		count_sub_dollar(mini, i);
}

// main parsing func, block++ for amount of char** necessary to malloc.
static void	count_blocks(t_minishell *mini)
{
	int	i;

	i = 0;
	while (mini->arg[i])
	{
		if (mini->arg[i] == '\'')
			end_quote(mini, &i);
		else if (mini->arg[i] == '\"')
			end_doublequote(mini, &i);
		else if (mini->arg[i] == '|')
			mini->parse.block_count++;
		i++;
	}
	mini->parse.block_count++;
}

static void	parse(t_minishell *mini)
{
	int	i;

	i = 0;
	mini->cmd = malloc(sizeof(char **) * (mini->parse.block_count + 1));
	if (!mini->cmd)
		parse_exit(mini);
	while (mini->arg[i])
	{
		while (mini->arg[i] && mini->arg[i] != '|')
		{
			if (mini->arg[i] == '|')
			
			i++;
		}
		
	}
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
		count_blocks(mini);
		parse(mini);
		free(mini->arg);
	}
}
