/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:03:35 by araymond          #+#    #+#             */
/*   Updated: 2023/09/06 09:30:32 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	malloc_error(t_minishell *mini)
{
	mini->exit_code = 1;
	write(STDOUT_FILENO, "malloc error\n", 13);
	exit_program(mini);
}