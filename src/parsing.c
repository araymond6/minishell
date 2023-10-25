#include "../include/minishell.h"

void	read_input(t_minishell *mini)
{
	while (1)
	{
		signal_reset(mini);
		mini->arg = readline("\033[92mminishell % \033[0m");
		if (mini->arg == NULL)
			break ;
		if (mini->arg[0] == '\0' || whitespace_check(mini->arg))
		{
			free(mini->arg);
			continue ;
		}
		add_history(mini->arg);
		mini->token = tokenize(mini, mini->arg);
		if (mini->token)
		{
			int i = 0;

			while (i < mini->token_count)
			{
				printf("%s\n", mini->token[i++].token);
			}
			// if (create_list(mini) == 0)
			// 	x_comm(mini);
		}
		clear_mini(mini);
	}
}