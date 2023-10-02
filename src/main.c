/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:15 by araymond          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/29 11:12:25 by vst-pier         ###   ########.fr       */
=======
/*   Updated: 2023/10/02 13:26:17 by araymond         ###   ########.fr       */
>>>>>>> 97a785bc1f5a6126876d4b436930c703f0804005
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	x_comm(t_minishell *mini)
{
	mini->s_cmd = NULL;
	create_list(mini);
	process(mini);
<<<<<<< HEAD
	free_scmd(mini->s_cmd);
	return(0);
}


//attention a la sortie lors des redirection termine dans le fd 
//
int main(int argc, char **argv, char **envp)
{
	t_minishell mini;
	(void) argc;
	(void) argv;
	
=======
	free(mini->s_cmd);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mini;

>>>>>>> 97a785bc1f5a6126876d4b436930c703f0804005
	if (!envp)
		exit(EXIT_FAILURE);
	initialize_mini(&mini, envp);
	read_input(&mini);
	exit_program(&mini);
}
