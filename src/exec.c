/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:45:48 by vst-pier          #+#    #+#             */
/*   Updated: 2023/08/07 15:48:24 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// function de depart de lexecution
void execution(t_minishell *mini)
{
	int i;
	
	i = 0;
	while(mini->cmd[i] != NULL)
	{
		parsing_command(mini, i);
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_minishell *mini;
	
	(void) argc;
	(void) argv;
	mini = ft_calloc(1, sizeof(t_minishell));
	save_path(mini, envp);
	mini->arg = NULL;
	mini->cmd = ft_calloc(4, sizeof(char*));
	mini->cmd[0] = ft_calloc(28, sizeof(char));
	mini->cmd[0] = "< allo.txt ls -la >> txt.txt";
	mini->cmd[1] = ft_calloc(16, sizeof(char));
	mini->cmd[1] = "cat -e >txt.txt";
	mini->cmd[2] = ft_calloc(12, sizeof(char));
	mini->cmd[2] = "<<END wc -l";
	mini->cmd[3] = ft_calloc(1, sizeof(char));
	mini->cmd[3] = NULL;
	mini->struct_cmd = NULL;
	execution(mini);
}