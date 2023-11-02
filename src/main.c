#include "../include/minishell.h"

t_minishell	*minishell(t_minishell *mini)
{
	static t_minishell *stat = NULL;

	if (mini)
		stat = mini;
	return (stat);
}

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
