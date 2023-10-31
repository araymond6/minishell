#include "../include/minishell.h"

static int	quotestr_loop(t_minishell *mini, t_token *tokens, char *arg, int *i)
{
	t_type	quote_type;
	int		error;

	quote_type = tokens->type;
	error = 0;
	i[0]++;
	tokens->type = get_type(&arg[i[0]]);
	while (tokens->type != quote_type && arg[i[0]])
	{
		if (tokens->type == DOLLAR_SIGN && quote_type == DOUBLE_QUOTE)
		{
			error = do_substitution(mini, tokens, arg, i);
		}
		else
		{
			tokens->token[i[1]++] = arg[i[0]++];
		}
		tokens->type = get_type(&arg[i[0]]);
	}
	i[0]++;
	tokens->type = get_type(&arg[i[0]]);
	return (0);
}

int	get_token_str_loop(t_minishell *mini, t_token *tokens, char *arg, int *i)
{
	while ((tokens->type == STRING || tokens->type == SINGLE_QUOTE \
		|| tokens->type == DOUBLE_QUOTE) && arg[i[0]])
	{
		if (tokens->type == SINGLE_QUOTE || tokens->type == DOUBLE_QUOTE)
		{
			if (quotestr_loop(mini, tokens, arg, i))
				return (1);
			tokens->inquote = 1;
		}
		else if (tokens->type == STRING)
		{
			while (tokens->type == STRING && arg[i[0]])
			{
				tokens->token[i[1]++] = arg[i[0]++];
				tokens->type = get_type(&arg[i[0]]);
			}
		}
		if (tokens->type == DOLLAR_SIGN || whitespace_check(&arg[i[0]]))
			return (2);
	}
	tokens->type = STRING;
	return (0);
}
