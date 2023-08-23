/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublequote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:47:11 by araymond          #+#    #+#             */
/*   Updated: 2023/08/22 15:41:50 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	substitute_dollar(t_minishell *mini, int *i, int *j)
{
	int		k;
	char	*var;

	k = (*j);
	while (mini->arg[*i + k] )
}

void	doublequote_parse(t_minishell *mini, int *i)
{
	int	j;

	j = 0;
	(*i)++;
	while (mini->arg[*i + j] && mini->arg[*i + j] != '\"')
	{
		if (mini->arg[*i + j] == '$')
		{
			j++;
			substitute_dollar(mini, i, &j);
		}
		j++;
	}
	
}