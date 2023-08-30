/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:48:30 by araymond          #+#    #+#             */
/*   Updated: 2023/08/29 15:17:40 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_exit(t_minishell *mini)
{
	perror("Error");
	exit_program(mini);
}

void	parsing_error(t_minishell *mini)
{
	mini->exit_code = 2;
	if (write(STDOUT_FILENO, "parse error\n", 15) == -1)
		parse_exit(mini);
}