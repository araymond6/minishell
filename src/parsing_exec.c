/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:04:28 by valerie           #+#    #+#             */
/*   Updated: 2023/09/29 11:10:54 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//parse the command for the command part, and redirections part 
void	parsing_command(t_minishell *mini, int i)
{
	int		j;

	j = 0;
	if (!mini->s_cmd)
	{
		mini->s_cmd = ft_calloc(1, sizeof(t_cmd));
		initialize_s_cmd(mini->s_cmd);
	}
	if (!mini->s_cmd->next)
	{
		mini->s_cmd->next = ft_calloc(1, sizeof(t_cmd));
		initialize_s_cmd(mini->s_cmd->next);
	}
	mini->s_cmd->nredir = redir_count(mini->cmd[i]);
	while (mini->cmd[i][j] && mini->cmd[i])
	{
		if (mini->cmd[i][j] == '<')
			j = entry_redirection(mini, i, j + 1);
		else if (mini->cmd[i][j] == '>')
			j = exit_redirection(mini, i, j + 1);
		else if (mini->cmd[i][j] == ' ')
			j++;
		else
			j = check_command(mini, i, j);
	}
}

// create the s_cmd list 
void	create_list(t_minishell *mini)
{
	int		i;
	t_cmd	*copy;

	i = 0;
	copy = ft_calloc(1, sizeof(t_cmd));
	while (mini->cmd[i] != NULL)
	{
		parsing_command(mini, i);
		copy = mini->s_cmd;
		mini->s_cmd = mini->s_cmd->next;
		mini->s_cmd->prev = copy;
		i++;
	}
	while (i-- > 0)
		mini->s_cmd = mini->s_cmd->prev;
}
