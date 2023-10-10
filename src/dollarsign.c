#include "../include/minishell.h"



// adds to mini->parse.sub the c count if found
void	add_sub_env(t_minishell *mini, char *arg)
{
	int		i;
	char	*new;

	i = 0;
	if (!arg || arg[0] == '\0')
		return ;
	new = check_env(mini, arg);
	if (!new || new[0] == '\0')
		return ;
	while (new[i] != '=')
		i++;
	i++;
	while (new[i])
	{
		mini->parse.sub++;
		i++;
	}
	free(new);
}

//adds the substitution of the env var to mini->cmd
void	add_from_env(t_minishell *mini, int *j, char *arg)
{
	char	*new;
	int		k;

	k = 0;
	new = check_env(mini, arg);
	if (!new || new[0] == '\0' || !arg || arg[0] == '\0')
		return ;
	while (new[k] != '=')
		k++;
	k++;
	while (new[k])
		mini->cmd[mini->parse.c][(*j)++] = new[k++];
	free(new);
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
