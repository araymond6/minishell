/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:55:58 by araymond          #+#    #+#             */
/*   Updated: 2023/09/28 17:01:53 by araymond         ###   ########.fr       */
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

int	export_parsing(t_minishell *mini, int *i)
{
	int		j;
	int		k;
	char	*str;

	j = 0;
	k = 0;
	if (ft_isdigit(mini->s_cmd->cmd_arg[*i][0]))
	return (1);
	str = ft_calloc(ft_strlen(mini->s_cmd->cmd_arg[*i] + 1), sizeof(char));
	if (!str)
		malloc_error(mini);
	while (mini->s_cmd->cmd_arg[*i][k] && mini->s_cmd->cmd_arg[*i][k] != '=')
	{
		if (mini->s_cmd->cmd_arg[*i][k] != '\'' || mini->s_cmd->cmd_arg[*i][k] != '\"')
			k++;
		else
			str[k++] = mini->s_cmd->cmd_arg[*i][j++];
	}
	return (0);
}


// finish unset first, then export



int	ft_export(t_minishell *mini)
{
	char	**table;
	int		i;

	i = 1;
	while (mini->s_cmd->cmd_arg[i])
	{
		if (!mini->s_cmd->cmd_arg[i] || mini->s_cmd->cmd_arg[i][0] == '\0')
		{
			printf("export: \"%s\": not a valid identifier", mini->s_cmd->cmd_arg[i]);
			i++;
			continue ;
		}
		if (export_parsing(mini, &i))
			return (message_perror("export"), 1);
		table = ft_calloc(i + 2, sizeof(char *));
		while (mini->envp[i])
		{
			table[i] = mini->envp[i];
			i++;
		}
		i++;
	}
	return (0);
}

int	unset_parsing(t_minishell *mini, int *i)
{
	int		j;
	int		k;
	char	*str;

	j = 0;
	k = 0;
	while (mini->envp)
	{
		
		
	}
	return (-1);
}

int	ft_unset(t_minishell *mini)
{
	char	**table;
	int		i;

	i = 1;
	while (mini->s_cmd->cmd_arg[i])
	{
		if (!mini->s_cmd->cmd_arg[i] || mini->s_cmd->cmd_arg[i][0] == '\0')
		{
			printf("unset: \"%s\": not a valid identifier", mini->s_cmd->cmd_arg[i]);
			i++;
			continue ;
		}
		if (unset_parsing(mini, &i) == -1)
			return (message_perror("export"), 1);
		table = ft_calloc(i + 2, sizeof(char *));
		while (mini->envp[i])
		{
			table[i] = mini->envp[i];
			i++;
		}
		i++;
	}
}
