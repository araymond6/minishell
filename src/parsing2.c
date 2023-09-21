/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:24:44 by araymond          #+#    #+#             */
/*   Updated: 2023/09/21 14:29:35 by araymond         ###   ########.fr       */
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
	else if (mini->arg[*i] == ' ')
	{
		(*i)++;
		while (mini->arg[*i] == ' ')
			(*i)++;
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