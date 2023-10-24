#include "../include/minishell.h"

/*
// this is for types that usually are not by themselves, 
only adding a count after the entire sequence of characters

// this skips single characters that should be handled individually

make this smaller, somehow......
*/
int	count_tokens(t_minishell *mini, char *arg)
{
	t_type	type;
	int		count;
	t_type	quote_type;

	count = 0;
	while (arg[0])
	{
		type = get_type(arg);
		if (type == WHITESPACE)
		{
			while (type == WHITESPACE && arg[0])
			{
				arg++;
				type = get_type(arg);
			}
		}
		else if ((type == DOLLAR_SIGN && (arg[1] != '?' || arg[1] != '_' || !ft_isalnum(arg[1]))) || \
			type == REDIRECT_INPUT || type == REDIRECT_OUTPUT)
		{
			arg++;
			count++;
		}
		else if (type == PIPE)
			arg++;
		else if (type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
		{
			quote_type = get_type(arg);
			arg++;
			while (type != quote_type && arg[0])
			{
				arg++;
				type = get_type(arg);
			}
			if (type != quote_type)
				return (parsing_error(mini), 1);
			arg++;
			count++;
		}
		else if (type == APPEND || type == HERE_DOC)
		{
			arg += 2;
			count++;
		}
		else if (type == STRING && (arg[1] == '\'' || arg[1] == '\"'))
		{
			arg ++;
			quote_type = get_type(arg);
			arg++;
			while (type != quote_type && arg[0])
			{
				arg++;
				type = get_type(arg);
			}
			if (type != quote_type)
				return (parsing_error(mini), 1);
			arg++;
			count++;
		}
		else if (type == STRING)
		{
			while (type == STRING)
			{
				arg++;
				type = get_type(arg);
			}
			if (type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
			count++;
		}
		else if ((type == DOLLAR_SIGN && (ft_isalnum(arg[1]) || \
				arg[1] == '?' || arg[1] == '_')))
		{
			arg++;
			type = get_type(arg);
			while (arg[0] && arg[0] == '_' && ft_isalnum(arg))
				arg++;
			count++;
		}
	}
	return (count);
}