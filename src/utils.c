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

void	clear_2darrays(t_minishell *mini)
{
	
}