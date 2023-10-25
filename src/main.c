#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	mini;

	(void) argc;
	(void) argv;
	if (!envp)
		exit(EXIT_FAILURE);
	initialize_mini(&mini, envp);
	read_input(&mini);
	exit_program(&mini);
	return (0);
}
