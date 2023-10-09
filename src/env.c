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
		str[k++] = mini->s_cmd->cmd_arg[*i][j++];
	return (0);
}

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

// returns -1 if arg to unset not found, looks for the var to unset
int	unset_parsing(t_minishell *mini, int *i)
{
	int		j;
	int		k;
	char	*str;

	j = -1;
	k = 0;
	if (ft_isdigit(mini->s_cmd->cmd_arg[*i][0]))
		return (-2);
	str = ft_strjoin(mini->s_cmd->cmd_arg[*i], "="); // FIND OUT WHAT TO DO WITH MALLOC ERROR
	if (!str)
		malloc_error(mini);
	if (!str)
		return (-1);
	while (mini->envp[++j])
	{
		if (!ft_strncmp(mini->envp[j], str, ft_strlen(str)))
		{
			free(str);
			return (j);
		}
	}
	free(str);
	return (-1);
}

int	ft_unset(t_minishell *mini)
{
	int		i;
	int		j;
	int		k;
	int		c;
	char	**table;

	i = 1;
	j = 0;
	k = 0;
	table = NULL;
	while (mini->s_cmd->cmd_arg[i])
	{
		if (mini->s_cmd->cmd_arg[i][0] == '\0')
		{
			printf("unset: \"%s\": not a valid identifier\n", mini->s_cmd->cmd_arg[i++]);
			continue ;
		}
		c = unset_parsing(mini, &i);
		if (c == -1)
		{
			i++;
			continue ;
		}
		else if (c == -2)
		{
			printf("unset: \"%s\": not a valid identifier\n", mini->s_cmd->cmd_arg[i++]);
			continue ;
		}
		table = ft_calloc(count_2darray(mini->envp), sizeof(char *));
		if (!table)
			malloc_error(mini);
		while (mini->envp[k])
		{
			if (k == c)
			{
				k++;
				continue ;
			}
			table[j++] = mini->envp[k++];
			if (!mini->envp[k])
				table[j] = NULL;
		}
		if (mini->envpset)
			free_array(mini->envp);
		mini->envp = table;
		mini->envpset = 1;
		i++;
	}
	mini->exit_code = 0;
	return (0);
}
