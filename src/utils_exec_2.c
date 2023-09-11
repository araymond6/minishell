/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerie <valerie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:54:01 by valerie           #+#    #+#             */
/*   Updated: 2023/09/11 15:57:51 by valerie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//this function count the nbrs of argument fot command
// ex: ls -l -a => 2 arguments
int	nbr_arg(t_minishell *mini, int i, int j)
{
	int	space;
	int	k;

	space = 0;
	k = 0;
	while (mini->cmd[i][j + k]
		&& mini->cmd[i][j + k] != '>'
		&& mini->cmd[i][j + k] != '<')
	{
		if (mini->cmd[i][j + k] == ' '
			&& mini->cmd[i][j + k + 1] != '>'
			&& mini->cmd[i][j + k + 1] != '<')
			space++;
		k++;
	}
	return (space);
}
