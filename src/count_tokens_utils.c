#include "../include/minishell.h"

static int	quote_loop(char *arg, int *i, t_type type, t_type quote_type)
{
	quote_type = type;
	(*i)++;
	type = get_type(&arg[*i]);
	while (type != quote_type && arg[*i])
	{
		(*i)++;
		type = get_type(&arg[*i]);
	}
	if (type != quote_type)
		return (-1);
	(*i)++;
	type = get_type(&arg[*i]);
	return (0);
}

int	count_string_loop(char *arg, int *i, t_type type, t_type quote_type)
{
	while ((type == STRING || type == SINGLE_QUOTE || \
		type == DOUBLE_QUOTE) && arg[*i])
	{
		if (type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
		{
			if (quote_loop(arg, i, type, quote_type) == -1)
				return (-1);
		}
		else if (type == STRING)
		{
			while (type == STRING && arg[*i])
			{
				(*i)++;
				type = get_type(&arg[*i]);
			}
		}
	}
	return (0);
}
