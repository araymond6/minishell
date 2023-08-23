/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:12 by araymond          #+#    #+#             */
/*   Updated: 2023/08/23 16:48:11 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_program(t_minishell *mini)
{
	rl_clear_history();
}

void	parse(t_minishell *mini)
{
	int	i;

	i = 0;
	while (mini->arg[i])
	{
		if (mini->arg[i] == '\\' || mini->arg[i] == ';')
			parsing_error(mini);
		else if (mini->arg[i] == '\'')
			quote_parse(mini, &i);
		else if (mini->arg[i] == '\"')
			doublequote_parse(mini, &i);
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
