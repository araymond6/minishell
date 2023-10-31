#include "../include/minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		kill(0, 0);
		printf("\n");
		rl_on_new_line();
	}
	else if (signal == SIGQUIT)
	{
		kill(0, 0);
		printf("\n");
		rl_on_new_line();
	}
}

void	signal_reset(t_minishell *mini)
{
	mini->sigact.sa_handler = signal_handler;
	sigaction(SIGINT, &mini->sigact, NULL);
	sigaction(SIGQUIT, &mini->sigact, NULL);
}

void	set_signal_for_process(t_minishell *mini)
{
	mini->sigact.sa_handler = sigint_handler;
	sigaction(SIGINT, &mini->sigact, NULL);
	sigaction(SIGQUIT, &mini->sigact, NULL);
}
