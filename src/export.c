/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:16:59 by araymond          #+#    #+#             */
/*   Updated: 2023/11/13 11:57:05 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* everything after the '=' is good, any non alnum 
char is wrong if before '=' except '_'
 returns -1 if not good and >=0 if VAR exists already. 
 returns -2 otherwise */
static int	export_parsing(t_minishell *mini, int *i, int j, int k)
{
	char	*str;
	char	*new;

	str = env_parsing(mini, i, &k);
	if (!str)
		return (-1);
	if (mini->s_cmd->cmd_arg[*i][k] != '=')
		return (free(str), -1);
	new = ft_strjoin(str, "=");
	free(str);
	if (!new)
		return (malloc_error(mini, NULL), -1);
	while (mini->envp[j])
	{
		if (!ft_strncmp(mini->envp[j], new, ft_strlen(new)))
		{
			free(new);
			return (j);
		}
		j++;
	}
	free(new);
	return (-2);
}

static int	export_error_check(t_minishell *mini, int *i, int *c)
{
	if (mini->s_cmd->cmd_arg[*i][0] == '\0' \
	|| ft_isdigit(mini->s_cmd->cmd_arg[*i][0]) || \
	mini->s_cmd->cmd_arg[*i][0] == '=')
	{
		write(2, "Not a valid identifier\n", 24);
		mini->exit_code = 1;
		(*i)++;
		return (1);
	}
	*c = export_parsing(mini, i, 0, 0);
	if (*c == -1)
	{
		(*i)++;
		return (1);
	}
	return (0);
}

static int	add_to_table(t_minishell *mini, char **table, int *i, int *j)
{
	int	param;

	param = 0;
	table[*j] = ft_calloc(sizeof(char), \
	ft_strlen(mini->s_cmd->cmd_arg[*i]) + 1);
	if (!table[*j])
	{
		table[*j] = NULL;
		return (malloc_error(mini, table), 1);
	}
	while (mini->s_cmd->cmd_arg[*i][param])
	{
		table[*j][param] = mini->s_cmd->cmd_arg[*i][param];
		param++;
	}
	if (!ft_strncmp(table[*j], "PATH=", 5))
		mini->path = table[*j];
	(*j)++;
	return (0);
}

static char	**export_table(t_minishell *mini, int *i, int *c)
{
	int		j;
	int		param;
	char	**table;

	if (*c >= 0)
		table = ft_calloc(count_2darray(mini->envp) + 1, sizeof(char *));
	else
		table = ft_calloc(count_2darray(mini->envp) + 2, sizeof(char *));
	if (!table)
	{
		(*i)++;
		return (NULL);
	}
	j = 0;
	param = while_table(mini, &j, c, table);
	if (param == 0)
	{
		if (add_to_table(mini, table, i, &j) == 1)
			return (NULL);
	}
	table[j] = NULL;
	(*i)++;
	return (table);
}

int	ft_export(t_minishell *mini)
{
	char	**table;
	int		i;
	int		c;

	i = 1;
	if (!mini->s_cmd->cmd_arg[i])
		print_env(mini);
	while (mini->s_cmd->cmd_arg[i])
	{
		if (export_error_check(mini, &i, &c) == 1)
			continue ;
		table = export_table(mini, &i, &c);
		if (!table)
			continue ;
		if (mini->envpset == 1)
			free_array(mini->envp);
		mini->envp = table;
		mini->envpset = 1;
	}
	return (0);
}
