/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:24:51 by araymond          #+#    #+#             */
/*   Updated: 2023/10/02 14:13:19 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


//Cas qui marche pas: pas d'alnum ou de <>

int	redir_parsing(t_minishell *mini)
{
	int	i;
	int	c;
	int	count;

	c = 0;
	while (mini->cmd[c])
	{
		i = 0;
		count = 0;
		printf("%s\n", mini->cmd[c]);
		while (mini->cmd[c][i])
		{
			if (count > 2)
				return (parsing_error(mini), 0);
			if (mini->cmd[c][i] == '<')
			{
				i++;
				count++;
				if (mini->cmd[c][i] == '>' || !mini->cmd[c][i])
					return (parsing_error(mini), 0);
			}
			else if (mini->cmd[c][i] == '>')
			{
				i++;
				count++;
				if (mini->cmd[c][i] == '<' || !mini->cmd[c][i])
					return (parsing_error(mini), 0);
			}
			else if ((count == 2 || count == 1) && \
			((!ft_isalnum(mini->cmd[c][i]) && mini->cmd[c][i] != ' ') || !mini->cmd[c][i]))
				return (parsing_error(mini), 0);
			else
			{
				i++;
				count = 0;
			}
		}
		c++;
	}
	return (0);
}