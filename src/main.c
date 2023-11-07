/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:16:48 by araymond          #+#    #+#             */
/*   Updated: 2023/11/06 15:55:56 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	reset_stdin_stdout(t_minishell *mini)
{
	if (dup2(mini->s_cmd->fd_stdin, STDIN_FILENO) == -1)
		message_perror("Impossible to restore stdin");
	close(mini->s_cmd->fd_stdin);
	if (dup2(mini->s_cmd->fd_stdout, STDOUT_FILENO) == -1)
		message_perror("Impossible to restore stdout");
	close(mini->s_cmd->fd_stdout);
}

void	time_to_execute(t_minishell *mini)
{
	mini->s_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!mini->s_cmd)
		return ;
	if (initialize_s_cmd(mini) == 1)
		return ;
	if (all_here_doc2(mini) == 1 || mini->sigint == 1)
	{
		reset_stdin_stdout(mini);
		supp_here_doc_file(mini);
		return ;
	}
	if (check_redirect_input(mini) == 1)
	{
		reset_stdin_stdout(mini);
		supp_here_doc_file(mini);
		free_scmd(mini->s_cmd);
		return ;
	}
	set_signal_for_process(mini);
	forker2(mini);
	time_to_wait(mini);
	reset_stdin_stdout(mini);
	supp_here_doc_file(mini);
	free_scmd(mini->s_cmd);
}

// clears history, frees mini's used resources and exits program
void	exit_program(t_minishell *mini)
{
	int	exit_code;

	exit_code = mini->exit_code;
	clear_history();
	clear_mini(mini);
	if (mini->envpset == 1)
		free_array(mini->envp);
	exit(exit_code);
}

t_minishell	*minishell(t_minishell *mini)
{
	static t_minishell	*stat;

	if (mini)
		stat = mini;
	return (stat);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mini;

	(void) argc;
	(void) argv;
	if (!envp)
		exit(EXIT_FAILURE);
	initialize_mini(&mini, envp);
	read_input(&mini);
	exit_program(&mini);
	return (0);
}
