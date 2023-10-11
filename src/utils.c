#include "../include/minishell.h"

// clears history, frees mini's uses and exits program
void	exit_program(t_minishell *mini)
{
	int	exit_code;

	exit_code = mini->exit_code;
	clear_history();
	free_mini(mini);
	exit(exit_code);
}

int	count_2darray(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		i++;
	return (i);
}

int	spacentabs_check(t_minishell *mini)
{
	int	i;

	i = 0;
	while (mini->arg[i])
	{
		while (mini->arg[i] == ' ')
		{
			i++;
		}
		while (mini->arg[i] == '\t')
		{
			i++;
		}
		if (mini->arg[i] != ' ' && mini->arg[i] != '\t' && mini->arg[i] != '\0')
			return (0);
	}
	return (1);
}
