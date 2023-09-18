/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublequote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:47:11 by araymond          #+#    #+#             */
/*   Updated: 2023/09/18 12:57:57 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	doublequote_cmd(t_minishell *mini, int *i, int *j)
{
	mini->cmd[mini->parse.c][(*j)++] = mini->arg[(*i)++];
	while (mini->arg[*i] && mini->arg[*i] != '\"')
	{
		if (mini->arg[*i] == '$')
			sub_dollar(mini, i, j);
		mini->cmd[mini->parse.c][(*j)++] = mini->arg[(*i)++];
	}
}

int	end_doublequote(t_minishell *mini, int *i)
{
	(*i)++;
	while (mini->arg[*i] && mini->arg[*i] != '\'')
		(*i)++;
	if (mini->arg[*i] != '\'')
		return (1);
	return (0);
}

void	doublequote_parse(t_minishell *mini, int *i)
{
	(*i)++;
	while (mini->arg[*i] && mini->arg[*i] != '\"')
	{
		if (mini->arg[*i] == '$')
			count_sub_dollar(mini, i);
		(*i)++;
	}
}