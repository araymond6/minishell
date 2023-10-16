#include "../include/minishell.h"

int	heredoc_sub(t_minishell *mini, char *new_line, char *new_sub)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	mini->arg = new_line;
	mini->parse.sub = 0;
	while (mini->arg[i])
	{
		if (mini->arg[i] == '$')
			error = count_sub_dollar(mini, &i); // TODO: make it work with mini->arg, even if it's in heredoc
		else
			i++;
		if (error == 1)
			return (free(new_line), 1);
	}
	i = 0;
}