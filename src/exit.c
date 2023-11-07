/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:17:04 by araymond          #+#    #+#             */
/*   Updated: 2023/11/07 11:10:25 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_exit_code(t_minishell *mini)
{
	int	i;

	i = 0;
	if (mini->s_cmd->cmd_arg[1][0] == '+' || \
		mini->s_cmd->cmd_arg[1][0] == '-')
		i++;
	while (mini->s_cmd->cmd_arg[1][i])
	{
		if (mini->s_cmd->cmd_arg[1][i] >= '0' \
			&& mini->s_cmd->cmd_arg[1][i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_exit_2plus_arg(t_minishell *mini, int nb_arg)
{
	if (nb_arg > 2)
	{
		if (is_valid_exit_code(mini) == 0)
		{
			mini->exit_code = 1;
			return (printf("Too many arguments\n"), 1);
		}
		supp_here_doc_file(mini);
		close(mini->s_cmd->fd_stdin);
		close(mini->s_cmd->fd_stdout);
		free_scmd(mini->s_cmd);
		exit_program(mini);
	}
	return (0);
}

void	ft_exit_1_arg(t_minishell *mini, int nb_arg)
{
	if (nb_arg == 2)
	{
		if (is_valid_exit_code(mini) == 1)
		{
			printf("Not a numeric argument\n");
			mini->exit_code = 255;
		}
		else
			mini->exit_code = ft_atoll(mini->s_cmd->cmd_arg[1]);
		supp_here_doc_file(mini);
		close(mini->s_cmd->fd_stdin);
		close(mini->s_cmd->fd_stdout);
		free_scmd(mini->s_cmd);
		exit_program(mini);
	}
}

int	ft_exit(t_minishell *mini)
{
	int	nb_arg;

	nb_arg = 0;
	close(mini->s_cmd->pipe[1]);
	close(mini->s_cmd->pipe[0]);
	while (mini->s_cmd->cmd_arg[nb_arg])
		nb_arg++;
	if (nb_arg == 1)
	{
		supp_here_doc_file(mini);
		close(mini->s_cmd->fd_stdin);
		close(mini->s_cmd->fd_stdout);
		free_scmd(mini->s_cmd);
		exit_program(mini);
	}
	ft_exit_1_arg(mini, nb_arg);
	if (ft_exit_2plus_arg(mini, nb_arg))
		return (1);
	return (0);
}
