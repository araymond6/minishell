#include "../include/minishell.h"

int	get_token_type3(t_minishell *mini, t_token *tokens, char *arg, int *i)
{
	if ((tokens->type == DOLLAR_SIGN && (ft_isalnum(arg[*i + 1]) || \
			arg[*i + 1] == '?' || arg[*i + 1] == '_')))
	{
		if (new_substitution(mini, tokens, arg, i) == 1)
			return (1);
	}
	return (0);
}

int	str_loop2(t_minishell *mini, t_token *tokens, char *arg, int *i)
{
	t_type quote_type;

	quote_type = tokens->type;
	i[0]++;
	tokens->type = get_type(&arg[i[0]]);
	while (tokens->type != quote_type && arg[i[0]])
	{
		if (tokens->type == DOLLAR_SIGN && quote_type == DOUBLE_QUOTE && (ft_isalnum(arg[i[0] + 1]) || \
			arg[i[0] + 1] == '?' || arg[i[0] + 1] == '_'))
		{
			if (new_substitution(mini, tokens, arg, i) == 1)
				return (1);
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
			if (str_loop2(mini, tokens, arg, i))
				return (1);
		}
		else if (tokens->type == STRING)
		{
			while (tokens->type == STRING && arg[i[0]])
			{
				tokens->token[i[1]++] = arg[i[0]++]; //TODO: figure out why this is not working
				tokens->type = get_type(&arg[i[0]]);
			}
		}
	}
	tokens->type = STRING;
	return (0);
}

int	get_token_type2(t_minishell *mini, t_token *tokens, char *arg, int *i)
{
	if (tokens->type == APPEND || tokens->type == HERE_DOC)// 
	{
		tokens->token[i[1]++] = arg[i[0]++];
		tokens->token[i[1]++] = arg[i[0]++];
	}
	else if (tokens->type == STRING || tokens->type == SINGLE_QUOTE \
		|| tokens->type == DOUBLE_QUOTE)
	{
		if (get_token_str_loop(mini, tokens, arg, i) == 1)
			return (1);
	}
	else
		return (get_token_type3(mini, tokens, arg, i));
	return (0);
}

int	get_token_type(t_minishell *mini, t_token *tokens, char *arg, int *i)
{
	tokens->type = get_type(&arg[i[0]]);
	if (tokens->type == WHITESPACE)
	{
		while (tokens->type == WHITESPACE && arg[i[0]])
		{
			i[0]++;
			return (2);
		}
	}
	else if ((tokens->type == DOLLAR_SIGN && (arg[i[0] + 1] != '?' || \
		arg[i[0] + 1] != '_' || !ft_isalnum(arg[i[0] + 1]))) || \
		tokens->type == REDIRECT_INPUT || tokens->type == REDIRECT_OUTPUT)
	{
		tokens->token[i[1]] = arg[i[0]];
		i[0]++;
	}
	else if (tokens->type == PIPE)
	{
		i[0]++;
		mini->cmd_n++;
		return (2);
	}
	else
		return (get_token_type2(mini, tokens, arg, i));
	return (0);
}

int	get_tokens(t_minishell *mini, t_token *tokens, char *arg)
{
	int		i[2];
	int		t;
	int		rtn;

	i[0] = 0;
	i[1] = 0;
	t = -1;
	rtn = 0;
	while (arg[i[0]])
	{
		if (rtn != 2)
		{
			t++;
			tokens[t].token = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
			if (!tokens[t].token)
				return (malloc_error(mini, NULL), 1);
		}
		tokens[t].cmd_n = mini->cmd_n;
		rtn = get_token_type(mini, &tokens[t], arg, i);
		if (rtn == 1)
			return (1);
		i[1] = 0;
	}
	return (0);
}