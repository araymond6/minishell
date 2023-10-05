/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerie <valerie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:52:22 by vst-pier          #+#    #+#             */
/*   Updated: 2023/09/29 18:30:58 by valerie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_scmd(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp)
	{
		if (temp->redir)
			free(temp->redir);
		if (temp->cmd)
			free(temp->cmd);
		if (temp->path)
			free(temp->path);
		if (temp->cmd_arg)
			free_array(temp->cmd_arg);
		if (cmd->file)
			free_array(temp->file);
		temp = temp->next;
		free(cmd);
		cmd = temp;
	}
}

void	ft_exit(t_minishell *mini)
{
	free_scmd(mini->s_cmd);
	mini->exit_code = 0;
	exit_program(mini);
}
