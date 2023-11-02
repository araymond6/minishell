#include "../include/minishell.h"

char	*heredoc_extra(t_minishell *mini, char *new, int *i, char *new_line)
{
	new = heredoc_sub(mini, new, i, new_line);
	if (!new)
		return (NULL);
	new = ft_realloc(new, ft_strlen(new), ft_strlen(new) \
	+ ft_strlen(&new_line[*i]) + 1);
	if (!new)
		return (NULL);
	return (new);
}

// clears history, frees mini's used resources and exits program
void	exit_program(t_minishell *mini)
{
	int	exit_code;

	exit_code = mini->exit_code;
	clear_history();
	clear_mini(mini);
	if (mini->envpset == 1)
		free_array(mini->envp);
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
int	whitespace_check(char *str)
{
	t_type	type;
	int		i;

	i = 0;
	type = get_type(str + i);
	while (type == WHITESPACE)
	{
		i++;
		type = get_type(str + i);
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	skip_whitespace(char *arg, int *i)
{
	while (get_type(&arg[*i]) == WHITESPACE)
		(*i)++;
}

int	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	long long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (sign * nb);
}
