#include "../include/minishell.h"

// int	count_heredoc(t_minishell *mini, int count)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (mini->cmd[i])
// 	{
// 		j = 0;
// 		while (mini->cmd[i][j])
// 		{
// 			if (mini->cmd[i][j] == '<')
// 			{
// 				j++;
// 				if (mini->cmd[i][j] == '<')
// 				{
// 					j++;
// 					count++;
// 				}
// 			}
// 			else
// 				j++;
// 		}
// 		i++;
// 	}
// 	return (count);
// }

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

// checks for space and tabs to see if it's ONLY that
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
