/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:17:19 by araymond          #+#    #+#             */
/*   Updated: 2023/11/06 16:34:54 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	nb_of_arg_lopp(int i, int n, t_minishell *mini)
{
	while (i < mini->token_count && mini->token[i].cmd_n == n)
	{
		if (mini->token[i].type == HERE_DOC
			|| mini->token[i].type == APPEND
			|| mini->token[i].type == REDIRECT_INPUT
			|| mini->token[i].type == REDIRECT_OUTPUT)
			i += 2;
		else
		{
			while (i < mini->token_count
				&& mini->token[i].cmd_n == n
				&& mini->token[i].type == STRING)
			{
				i++;
				mini->s_cmd->narg++;
			}
		}
	}
}

void	nb_of_arg(t_minishell *mini, int n)
{
	int	i;

	i = 0;
	mini->s_cmd->narg = 0;
	while (i < mini->token_count && mini->token[i].cmd_n != n)
		i++;
	nb_of_arg_lopp(i, n, mini);
}

void	cpy_cmd_loop(t_minishell *mini, int i, int r)
{
	mini->s_cmd->cmd_arg[r] = \
	ft_calloc(ft_strlen(mini->token[i].token) + 1, sizeof(char));
	if (!mini->s_cmd->cmd_arg[r])
	{
		malloc_error(mini, mini->s_cmd->cmd_arg);
		return ;
	}
	if (mini->token[i].inquote == 0 && mini->token[i].token[0] == 0)
		mini->s_cmd->cmd_arg[r] = NULL;
	else
	{
		ft_strlcpy(mini->s_cmd->cmd_arg[r], mini->token[i].token,
			ft_strlen(mini->token[i].token) + 1);
	}
}

void	cpy_cmd(t_minishell *mini, int n, int i)
{
	int	r;

	r = 0;
	while (i < mini->token_count && mini->token[i].cmd_n == n)
	{
		if (mini->token[i].type != STRING)
			i += 2;
		else
		{
			while (i < mini->token_count
				&& mini->token[i].cmd_n == n
				&& mini->token[i].type == STRING)
			{
				cpy_cmd_loop(mini, i, r);
				i++;
				r++;
			}
		}
	}
}

void	find_cmd(t_minishell *mini, int n)
{
	int	i;

	i = 0;
	nb_of_arg(mini, n);
	mini->s_cmd->cmd_arg = ft_calloc(mini->s_cmd->narg + 1, sizeof(char *));
	if (!mini->s_cmd->cmd_arg)
	{
		malloc_error(mini, NULL);
		mini->s_cmd->cmd_arg = NULL;
		return ;
	}
	while (i < mini->token_count && mini->token[i].cmd_n != n)
		i++;
	while (i < mini->token_count && mini->token[i].cmd_n == n)
	{
		if (mini->token[i].type == HERE_DOC
			|| mini->token[i].type == APPEND
			|| mini->token[i].type == REDIRECT_INPUT
			|| mini->token[i].type == REDIRECT_OUTPUT)
			i += 2;
		else
			return (cpy_cmd(mini, n, i));
	}
}
