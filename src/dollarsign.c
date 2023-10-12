#include "../include/minishell.h"

// adds to mini->parse.sub the c count if found
int	add_sub_env(t_minishell *mini, char *arg)
{
	int		i;
	char	*new;

	i = 0;
	if (!arg || arg[0] == '\0')
		return (0);
	new = check_env(mini, arg);
	if (!new || new[0] == '\0')
		return (1);
	while (new[i] != '=')
		i++;
	i++;
	while (new[i])
	{
		mini->parse.sub++;
		i++;
	}
	free(new);
	return (0);
}

//adds the substitution of the env var to mini->cmd
int	add_from_env(t_minishell *mini, int *j, char *arg)
{
	char	*new;
	int		k;

	k = 0;
	new = check_env(mini, arg);
	if (!new || new[0] == '\0' || !arg || arg[0] == '\0')
		return (1);
	while (new[k] != '=')
		k++;
	k++;
	while (new[k])
		mini->cmd[mini->parse.c][(*j)++] = new[k++];
	free(new);
	return (0);
}

//exit_code exception
void	add_exitcode(t_minishell *mini, int *j, char *arg)
{
	int	k;

	k = -1;
	while (arg[++k])
	{
		mini->cmd[mini->parse.c][(*j)++] = arg[k];
	}
}
