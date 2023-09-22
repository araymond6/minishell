/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:20:31 by araymond          #+#    #+#             */
/*   Updated: 2023/09/22 14:34:17 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// zeroes t_minishell and set envp
void	initialize_mini(t_minishell *mini, char **envp)
{
	ft_bzero(mini, sizeof(t_minishell));
	mini->envp = envp;
	mini->sigact.sa_handler = signal_handler;
	mini->exit_code = 127;
	sigaction(SIGINT, &mini->sigact, NULL);
	sigaction(SIGQUIT, &mini->sigact, NULL);
}

// will need at some point
void	free_mini(t_minishell *mini)
{
	int	i;

	i = -1;
	if (mini->cmd)
	{
		while (mini->cmd[++i])
			free(mini->cmd[i]);
		free(mini->cmd);
		mini->cmd = NULL;
	}
}

void	clear_mini(t_minishell *mini)
{
	mini->parse.block_count = 0;
	mini->parse.c = 0;
	mini->parse.end_block = 0;
	mini->parse.start_block = 0;
	mini->parse.sub = 0;
}

// clears history, frees mini's uses and exits program with exit_code depending on the error seen or not seen
void	exit_program(t_minishell *mini)
{
	int exit_code;

	exit_code = mini->exit_code;
	printf("exit code: %d\n", mini->exit_code);	
	clear_history();
	free_mini(mini);
	exit(exit_code);
}
