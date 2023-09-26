/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_cmd_attribution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:53:16 by valerie           #+#    #+#             */
/*   Updated: 2023/09/26 13:22:23 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//initialize s_cmd
void	initialize_s_cmd(t_cmd *cmd)
{
	cmd->redir = NULL;
	cmd->cmd = NULL;
	cmd->path = NULL;
	cmd->cmd_arg = NULL;
	cmd->file = NULL;
	cmd->next = NULL;
	cmd->nredir = 0;
	cmd->prev = ft_calloc(1, sizeof(t_cmd));
	cmd->redir = NULL;
	cmd->narg = 0;
	cmd->status = 0;
}

// s_cmd : attribute a value to cmd
int	s_cmd_cmd(t_minishell *mini, int i, int j)
{
	int	len_cmd;

	len_cmd = len_until_space(mini, i, j);
	mini->s_cmd->cmd = ft_calloc(len_cmd + 1, sizeof(char));
	j = ft_strjcpy(mini->s_cmd->cmd, mini->cmd[i], len_cmd, j);
	return (j);
}

// s_cmd : attribute a value to arg_cmd[0]
int	s_cmd_arg_cmd_first(t_minishell *mini)
{
	int	len;

	len = ft_strlen(mini->s_cmd->path);
	mini->s_cmd->cmd_arg[0] = ft_calloc(len + 1, sizeof(char));
	if (!mini->s_cmd->cmd_arg[0])
		return (-1);
	ft_strlcpy(mini->s_cmd->cmd_arg[0], mini->s_cmd->path, len + 1);
	return (0);
}

// s_cmd : attribute a value to arg_cmd betwenn arg_cmd[0] and arg_cmd[last]
int	s_cmd_arg_cmd_middle(t_minishell *mini, int i, int j, int k)
{
	int	len;

	len = len_until_space(mini, i, j);
	mini->s_cmd->cmd_arg[k] = ft_calloc(len + 1, sizeof(char));
	if (!mini->s_cmd->cmd_arg[k])
		return (-1);
	j = ft_strjcpy(mini->s_cmd->cmd_arg[k], mini->cmd[i], len, j);
	if (mini->cmd[i][j] == ' ')
		j++;
	return (j);
}

// s_cmd : attribute a value to arg_cmd[last]
int	s_cmd_arg_cmd_end(t_minishell *mini, int i, int j, int k)
{
	int	len_space;
	int	len_redirection;
	int	len;

	len_space = len_until_space(mini, i, j);
	len_redirection = len_until_redirections(mini, i, j);
	if (len_space < len_redirection)
		len = len_space;
	else
		len = len_redirection;
	mini->s_cmd->cmd_arg[k] = ft_calloc(len + 1, sizeof(char));
	if (!mini->s_cmd->cmd_arg[k])
		return (-1);
	j = ft_strjcpy(mini->s_cmd->cmd_arg[k], mini->cmd[i], len, j);
	if (mini->cmd[i][j] == ' ')
		j++;
	return (j);
}
