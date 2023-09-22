/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:26:24 by valerie           #+#    #+#             */
/*   Updated: 2023/09/22 14:45:08 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	x_comm(t_minishell *mini)
{
	mini->s_cmd = NULL;
	create_list(mini);
	process(mini->s_cmd);
	free(mini->s_cmd);
	free(mini);
	return(0);
}

//TODO here doc quand il y a des pipes
// int	main(int argc, char **argv, char **envp)
// {
// 	t_minishell	*mini;

// 	(void) argc;
// 	(void) argv;
// 	mini = ft_calloc(1, sizeof(t_minishell));
// 	mini->envp = envp;
// 	mini->arg = NULL;
// 	mini->cmd = ft_calloc(4, sizeof(char *));
// 	mini->cmd[0] = ft_calloc(28, sizeof(char));
// 	mini->cmd[0] = "< Makefile cat -e";
// 	mini->cmd[1] = ft_calloc(28, sizeof(char));
// 	mini->cmd[1] = "grep NAME";
// 	mini->cmd[2] = ft_calloc(28, sizeof(char));
// 	mini->cmd[2] = "wc >> allo.txt";
// 	mini->cmd[3] = ft_calloc(1, sizeof(char));
// 	mini->s_cmd = NULL;
// 	create_list(mini);
// 	process(mini->s_cmd);
// 	free(mini->s_cmd);
// 	free(mini);
// }
