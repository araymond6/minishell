/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerie <valerie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:26:24 by valerie           #+#    #+#             */
/*   Updated: 2023/09/11 16:40:31 by valerie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;

	(void) argc;
	(void) argv;
	mini = ft_calloc(1, sizeof(t_minishell));
	save_path(mini, envp);
	mini->arg = NULL;
	mini->cmd = ft_calloc(4, sizeof(char *));
	mini->cmd[0] = ft_calloc(28, sizeof(char));
	mini->cmd[0] = "< Makefile cat";
	mini->cmd[1] = ft_calloc(28, sizeof(char));
	mini->cmd[1] = "grep NAME";
	mini->cmd[2] = ft_calloc(28, sizeof(char));
	mini->cmd[2] = "wc";
	mini->cmd[3] = ft_calloc(1, sizeof(char));
	mini->cmd[3] = NULL;
	mini->s_cmd = NULL;
	create_list(mini);
	process(mini->s_cmd);
}
