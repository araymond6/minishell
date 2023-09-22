/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:15 by araymond          #+#    #+#             */
/*   Updated: 2023/09/22 14:45:09 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	x_comm(t_minishell *mini)
{

	mini->s_cmd = NULL;
	create_list(mini);
	process(mini->s_cmd);
	free(mini->s_cmd);
	return(0);
}

int main(int argc, char **argv, char **envp)
{
	t_minishell mini;
	
	initialize_mini(&mini, envp);
	read_input(&mini);
	exit_program(&mini);
}
