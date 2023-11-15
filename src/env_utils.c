/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:17:09 by araymond          #+#    #+#             */
/*   Updated: 2023/11/13 11:57:18 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_table(t_minishell *mini, char **table, int *j, int *k)
{
	int	l;

	l = 0;
	table[*j] = ft_calloc(sizeof(char), ft_strlen(mini->envp[*k]) + 1);
	if (!table[*j])
		return (1);
	while (mini->envp[*k][l])
	{
		table[*j][l] = mini->envp[*k][l];
		l++;
	}
	(*j)++;
	(*k)++;
	return (0);
}

int	while_table(t_minishell *mini, int *j, int *c, char **table)
{
	int	k;
	int	param;

	k = 0;
	while (mini->envp[k])
	{
		if (k == *c)
		{
			k++;
			continue ;
		}
		param = set_table(mini, table, j, &k);
		if (param == 1)
			return (1);
	}
	return (0);
}

void	print_env(t_minishell *mini)
{
	int	i;
	int	j;

	i = 0;
	while (mini->envp[i])
	{
		printf("declare -x ");
		j = 0;
		while (mini->envp[i][j] != '=')
			printf("%c", mini->envp[i][j++]);
		printf("%c", mini->envp[i][j++]);
		printf("\"");
		while (mini->envp[i][j])
			printf("%c", mini->envp[i][j++]);
		printf("\"\n");
		i++;
	}
}

char	*env_parsing(t_minishell *mini, int *i, int *j)
{
	char	*str;

	str = ft_calloc(ft_strlen(mini->s_cmd->cmd_arg[*i]) + 1, sizeof(char));
	if (!str)
		return (malloc_error(mini, NULL), NULL);
	while (mini->s_cmd->cmd_arg[*i][*j] && mini->s_cmd->cmd_arg[*i][*j] != '=')
	{
		if (!ft_isalnum(mini->s_cmd->cmd_arg[*i][*j]))
		{
			if (mini->s_cmd->cmd_arg[*i][*j] != '_')
			{
				free(str);
				write(2, "Not a valid identifier\n", 24);
				mini->exit_code = 1;
				return (NULL);
			}
		}
		str[*j] = mini->s_cmd->cmd_arg[*i][*j];
		(*j)++;
	}
	return (str);
}
