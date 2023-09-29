/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:55:58 by araymond          #+#    #+#             */
/*   Updated: 2023/09/29 11:15:17 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env(t_minishell *mini)
{
	int	i;

	i = -1;
	while (mini->envp[++i])
		printf("%s\n", mini->envp[i]);
	return (0);
}

int	export_parsing(t_minishell *mini)
{
	int	i;

	i = 0;
	while (mini->s_cmd->cmd_arg[1][i])
	{
		if (!ft_isalnum(mini->s_cmd->cmd_arg[1][i]))
		i++;
	}
	
	return (0);
}

int	ft_export(t_minishell *mini)
{
	char	**table;
	int		i;
	
	i = 0;
	if (!mini->s_cmd->cmd_arg[1] || mini->s_cmd->cmd_arg[1][0] == '\0')
		return (0);
	if (export_parsing(mini))
		return (1);
	table = calloc(i + 2, sizeof(char *));
	i = 0;
	while (mini->envp[i])
	{
		table[i] = mini->envp[i];
		i++;
	}
	return (0);
}