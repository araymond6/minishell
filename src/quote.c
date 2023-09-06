/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:47:13 by araymond          #+#    #+#             */
/*   Updated: 2023/09/04 11:56:06 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
