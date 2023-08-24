/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:12 by araymond          #+#    #+#             */
/*   Updated: 2023/08/24 14:51:41 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sub_dollar(t_minishell *mini, int *i)
{
	
}

void	count_sub_dollar(t_minishell *mini, int *i)
{
	(*i)++;
	mini->parse.sub--;
	while ((mini->arg[*i] != ' ' || mini->arg[*i] != '$') && mini->arg[*i])
	{
		mini->parse.sub--;
		(*i)++;
	}
	if (mini->arg[*i] == '$')
	{
		mini->parse.sub--;
		(*i)++;
		count_sub_dollar(mini, i);
	}
}

static void	parse(t_minishell *mini)
{
	int	i;

	i = 0;
	while (mini->arg[i])
	{
		if (mini->arg[i] == '\'')
			quote_parse(mini, &i);
		else if (mini->arg[i] == '\"')
			doublequote_parse(mini, &i);
		else if (mini->arg[i] == '$')
			count_sub_dollar(mini, &i);
		else if (mini->arg[i] == '|')
		{
			
		}
		i++;
	}
}

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
