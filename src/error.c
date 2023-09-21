/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:03:35 by araymond          #+#    #+#             */
/*   Updated: 2023/09/21 16:35:09 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	malloc_error(t_minishell *mini)
{
	mini->exit_code = 1;
	write(STDOUT_FILENO, "malloc error\n", 13);
	exit_program(mini);
}