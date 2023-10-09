#include "../include/minishell.h"

int	x_comm(t_minishell *mini)
{
	mini->s_cmd = NULL;
	create_list(mini);
	process(mini);
	free(mini->s_cmd);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mini;

	if (!envp)
		exit(EXIT_FAILURE);
	initialize_mini(&mini, envp);
	read_input(&mini);
	exit_program(&mini);
}