#include "../include/minishell.h"

static char	*sub_exception(t_minishell *mini, int *i)
{
	char	*arg;
	int		k;

	k = 0;
	arg = ft_calloc((ft_strlen(&mini->arg[*i]) + 1), sizeof(char));
	if (!arg)
		return (malloc_error(mini, NULL), NULL);
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
int	sub_dollar(t_minishell *mini, int *i, int *j, char *str)
{
	char	*exception;
	char	*arg;

	arg = sub_exception(mini, i);
	if (!arg)
		return (1);
	if (mini->arg[*i] == '?' && mini->arg[*i - 1] == '$')
	{
		exception = ft_itoa(mini->exit_code);
		if (!exception)
			return (malloc_error(mini, NULL), 1);
		add_exitcode(j, exception, str);
		(*i)++;
		return (free(arg), 0);
	}
	if (add_from_env(mini, j, arg, str))
	{
		if (mini->arg[*i] == ' ' || \
		mini->arg[*i] == '\t' || mini->arg[*i] == '\n')
			(*i)++;
	}
	if (mini->arg[*i] == '$')
		sub_dollar(mini, i, j, str);
	return (free(arg), 0);
}

/* counts how many characters to remove and checks env to see
how many characters to add to it */
static char	*count_sub_exception(t_minishell *mini, int *i)
{
	char	*arg;
	int		j;

	j = 0;
	arg = ft_calloc((ft_strlen(&mini->arg[*i]) + 1), sizeof(char));
	if (!arg)
		return (malloc_error(mini, NULL), NULL);
	(*i)++;
	mini->parse.sub--;
	while (mini->arg[*i])
	{
		if (!ft_isalnum(mini->arg[*i]))
			break ;
		arg[j++] = mini->arg[(*i)++];
		mini->parse.sub--;
	}
	return (arg);
}

static int	exitcode_exception(t_minishell *mini, int *i)
{
	char	*exception;

	if (mini->arg[*i] == '?' && mini->arg[*i - 1] == '$')
	{
		exception = ft_itoa(mini->exit_code);
		if (!exception)
			return (malloc_error(mini, NULL), 1);
		mini->parse.sub += ft_strlen(exception);
		free(exception);
		(*i)++;
		return (0);
	}
	return (0);
}

int	count_sub_dollar(t_minishell *mini, int *i)
{
	char	*arg;

	arg = count_sub_exception(mini, i);
	if (!arg)
		return (1);
	if (exitcode_exception(mini, i))
	{
		free(arg);
		return (malloc_error(mini, NULL), 1);
	}
	if (add_sub_env(mini, arg))
	{
		if (mini->arg[*i] == ' ' || \
		mini->arg[*i] == '\t' || mini->arg[*i] == '\n')
			(*i)++;
	}
	if (mini->arg[*i] == '$')
		count_sub_dollar(mini, i);
	free(arg);
	return (0);
}