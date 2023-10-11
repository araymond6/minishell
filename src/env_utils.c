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