/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:24:44 by araymond          #+#    #+#             */
/*   Updated: 2023/09/04 12:53:47 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_block(t_minishell *mini, int *i, int *count)
{
	int	j;

	j = 0;
	while (j != *i)
	{
		
		mini->cmd[*count][j] = mini->arg[j];
	}
}