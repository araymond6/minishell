/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:47:13 by araymond          #+#    #+#             */
/*   Updated: 2023/09/20 10:22:14 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
