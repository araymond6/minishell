#include "../include/minishell.h"

int	x_comm(t_minishell *mini)
{
	//process(mini);
	free_scmd(mini->s_cmd);
	mini->s_cmd = NULL;
	return(0);
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
	return(0);
}
