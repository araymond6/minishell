/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublequote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:47:11 by araymond          #+#    #+#             */
/*   Updated: 2023/09/05 09:07:05 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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