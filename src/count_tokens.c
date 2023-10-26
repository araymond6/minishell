#include "../include/minishell.h"


int	count_string_loop(char *arg, int *i, t_type type, t_type quote_type)
{
	while ((type == STRING || type == SINGLE_QUOTE || type == DOUBLE_QUOTE) && arg[*i])
	{
		if (type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
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
		}
		else if (type == STRING)
		{
			while (type == STRING && arg[*i])
			{
				(*i)++;
				type = get_type(&arg[*i]);
			}
		}
		type = get_type(&arg[*i]);
	}
	return (0);
}

int	count_type3(char *arg, int *i, int *count, t_type type)
{
	if (type == DOLLAR_SIGN && (ft_isalnum(arg[*i + 1]) || \
			arg[*i + 1] == '?' || arg[*i + 1] == '_'))
	{
		(*i)++;
		type = get_type(arg);
		while (arg[*i] && (arg[*i] == '_' || ft_isalnum(arg[*i])))
			(*i)++;
		(*count)++;
	}
	return (0);
}

int	count_type2(char *arg, int *i, int *count, t_type type)
{
	t_type	quote_type;

	if (type == APPEND || type == HERE_DOC)
	{
		*i += 2;
		(*count)++;
	}
	else if (type == STRING || type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
	{
		if (count_string_loop(arg, i, type, 0) == -1)
			return (-1);
		(*count)++;
	}
	else
		return (count_type3(arg, i, count, type));
	return (0);
}

int	count_type(char *arg, int *i, int *count, t_type type)
{
	if (type == WHITESPACE)
	{
		while (type == WHITESPACE && arg[*i])
		{
			(*i)++;
			type = get_type(&arg[*i]);
		}
	}
	else if ((type == DOLLAR_SIGN && (arg[*i + 1] != '?' && arg[*i + 1] != '_' \
		&& !ft_isalnum(arg[*i + 1]))) || \
		type == REDIRECT_INPUT || type == REDIRECT_OUTPUT)
	{
		(*i)++;
		(*count)++;
	}
	else if (type == PIPE)
		(*i)++;
	else
		return (count_type2(arg, i, count, type));
	return (0);
}

int	count_tokens(t_minishell *mini, char *arg)
{
	t_type	type;
	t_type	quote_type;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (arg[i])
	{
		type = get_type(&arg[i]);
		if (count_type(arg, &i, &count, type) == -1)
			return (parsing_error(mini), -1);
	}
	return (count);
}