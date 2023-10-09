#include "../include/minishell.h"

int	ft_env(t_minishell *mini)
{
	int	i;

	i = -1;
	while (mini->envp[++i])
		printf("%s\n", mini->envp[i]);
	return (0);
}

// returns -1 if arg to unset not found, looks for the var to unset
static int	unset_parsing(t_minishell *mini, int *i)
{
	int		j;
	int		k;
	char	*str;

	j = 0;
	k = 0;
	str = env_parsing(mini, i, &k);
	if (!str)
		return (-1);
	if (mini->s_cmd->cmd_arg[*i][k] == '=')
		return (free(str), -1);
	str = ft_strjoin(mini->s_cmd->cmd_arg[*i], "=");
	if (!str)
		return (malloc_error(mini), -1);
	while (mini->envp[j])
	{
		if (!ft_strncmp(mini->envp[j], str, ft_strlen(str)))
		{
			free(str);
			return (j);
		}
		j++;
	}
	free(str);
	return (-1);
}

static int	unset_error_check(t_minishell *mini, int *i, int *c)
{
	if (mini->s_cmd->cmd_arg[*i][0] == '\0' || \
	ft_isdigit(mini->s_cmd->cmd_arg[*i][0]))
	{
		printf("unset: \"%s\": not a valid identifier\n", \
		mini->s_cmd->cmd_arg[(*i)++]);
		return (1);
	}
	*c = unset_parsing(mini, i);
	if (*c == -1)
	{
		(*i)++;
		return (1);
	}
	return (0);
}

static char	**unset_table(t_minishell *mini, int *i, int *c)
{
	int		param;
	int		j;
	char	**table;

	table = ft_calloc(count_2darray(mini->envp), sizeof(char *));
	if (!table)
	{
		(*i)++;
		return (NULL);
	}
	j = 0;
	param = while_table(mini, &j, c, table);
	table[j] = NULL;
	(*i)++;
	if (param == 1)
		free_array(table);
	return (table);
}

int	ft_unset(t_minishell *mini)
{
	int		i;
	int		c;
	char	**table;

	i = 1;
	while (mini->s_cmd->cmd_arg[i])
	{
		if (unset_error_check(mini, &i, &c) == 1)
			continue ;
		table = unset_table(mini, &i, &c);
		if (table == NULL)
			continue ;
		if (mini->envpset == 1)
			free_array(mini->envp);
		mini->envp = table;
		mini->envpset = 1;
	}
	mini->exit_code = 0;
	return (0);
}
