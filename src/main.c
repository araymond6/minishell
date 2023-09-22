/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:15 by araymond          #+#    #+#             */
/*   Updated: 2023/09/22 16:15:52 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	x_comm(t_minishell *mini)
{
	mini->s_cmd = NULL;
	create_list(mini);
	process(mini);
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
