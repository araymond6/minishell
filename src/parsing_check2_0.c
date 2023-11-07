/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check2_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:16:35 by araymond          #+#    #+#             */
/*   Updated: 2023/11/03 18:34:33 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	checks_after2(t_minishell *mini, int *i)
{
	if (*i == mini->token_count)
		return (1);
	if (mini->token[*i].type == REDIRECT_INPUT
		|| mini->token[*i].type == REDIRECT_OUTPUT
		|| mini->token[*i].type == HERE_DOC
		|| mini->token[*i].type == APPEND)
		return (1);
	i++;
	return (0);
}

int	redir_parsing2(t_minishell *mini)
{
	int	i;

	i = 0;
	while (i < mini->token_count)
	{
		if (mini->token[i].type == REDIRECT_INPUT
			|| mini->token[i].type == REDIRECT_OUTPUT
			|| mini->token[i].type == HERE_DOC
			|| mini->token[i].type == APPEND)
		{
			i++;
			if (checks_after2(mini, &i) == 1)
				return (1);
		}
		else
			i++;
	}
	return (0);
}
