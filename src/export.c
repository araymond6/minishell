/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:59:05 by araymond          #+#    #+#             */
/*   Updated: 2023/10/12 10:51:24 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*env_parsing(t_minishell *mini, int *i, int *j)
{
	char	*str;

	str = ft_calloc(ft_strlen(mini->s_cmd->cmd_arg[*i]) + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (mini->s_cmd->cmd_arg[*i][*j] && mini->s_cmd->cmd_arg[*i][*j] != '=')
	{
		if (!ft_isalnum(mini->s_cmd->cmd_arg[*i][*j]))
		{
			if (mini->s_cmd->cmd_arg[*i][*j] != '_')
			{
				free(str);
				printf("export: \"%s\": not a valid identifier\n", \
				mini->s_cmd->cmd_arg[*i]);
				mini->exit_code = 1;
				return (NULL);
			}
		}
		str[*j] = mini->s_cmd->cmd_arg[*i][*j];
		(*j)++;
	}
	return (str);
}

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
		printf("export: \"%s\": not a valid identifier\n", \
		mini->s_cmd->cmd_arg[*i]);
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
	int param;

	param = 0;
	table[*j] = ft_calloc(sizeof(char), \
	ft_strlen(mini->s_cmd->cmd_arg[*i]) + 1); // do error check
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
