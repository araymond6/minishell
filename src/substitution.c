#include "../include/minishell.h"



static char	*sub_exception(t_minishell *mini, int *i)
{
	char	*arg;
	int		k;

	k = 0;
	arg = ft_calloc((ft_strlen(&mini->arg[*i]) + 1), sizeof(char));
	if (!arg)
		malloc_error(mini);
	(*i)++;
	while (mini->arg[*i])
	{
		if (!ft_isalnum(mini->arg[*i]))
			break ;
		arg[k++] = mini->arg[(*i)++];
	}
	return (arg);
}

// substitutes the $ARG in mini->arg[i] and puts it into mini->cmd[c][j]
int	sub_dollar(t_minishell *mini, int *i, int *j)
{
	char	*exception;
	char	*arg;

	arg = sub_exception(mini, i);
	if (mini->arg[*i] == '?' && mini->arg[*i - 1] == '$')
	{
		exception = ft_itoa(mini->exit_code);
		if (!exception)
			malloc_error(mini);
		add_exitcode(mini, j, exception);
		(*i)++;
		return (free(arg), 0);
	}
	add_from_env(mini, j, arg);
	if (mini->arg[*i] == '$')
		sub_dollar(mini, i, j);
	return (free(arg), 0);
}

static void	count_sub_exception(t_minishell *mini, char *arg, int *i)
{
	char	*exception;

	if (mini->arg[*i] == '?' && mini->arg[*i - 1] == '$')
	{
		exception = ft_itoa(mini->exit_code);
		if (!exception)
		{
			free(arg);
			malloc_error(mini);
		}
		mini->parse.sub += ft_strlen(exception);
		free(arg);
		free(exception);
		(*i)++;
		return ;
	}
	add_sub_env(mini, arg);
	if (mini->arg[*i] == '$')
		count_sub_dollar(mini, i);
	free(arg);
}

/* counts how many characters to remove and checks env to see
how many characters to add to it */
void	count_sub_dollar(t_minishell *mini, int *i)
{
	char	*arg;
	int		j;

	j = 0;
	arg = ft_calloc((ft_strlen(&mini->arg[*i]) + 1), sizeof(char));
	if (!arg)
		malloc_error(mini);
	(*i)++;
	mini->parse.sub--;
	while (mini->arg[*i])
	{
		if (!ft_isalnum(mini->arg[*i]))
			break ;
		arg[j++] = mini->arg[(*i)++];
		mini->parse.sub--;
	}
	count_sub_exception(mini, arg, i);
}
