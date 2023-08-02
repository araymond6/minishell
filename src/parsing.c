/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:12 by araymond          #+#    #+#             */
/*   Updated: 2023/08/01 16:08:35 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	parse(t_minishell *mini)
{
	int	i;

	while (mini->arg[i])
	{
		if (mini->arg[i] == '$')
		{
			printf("bonjour\n");
		}
		//else if (mini->arg[i] == '\'')
		// else if (mini->arg[i] == '\"')
		// else if (mini->arg[i] == '|')
		// else if (mini->arg[i] == '<')
		// else if (mini->arg[i] == '>')
		// else if (mini->arg[i] == ' ')
		i++;
	}
}

int	read_input(t_minishell *mini)
{
	while(1)
	{
		mini->arg = readline("\033[92mminishell % \033[0m");
		add_history(mini->arg);
		parse(mini);
		free(mini->arg);
	}
}
