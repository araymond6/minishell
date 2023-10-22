/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:43:51 by araymond          #+#    #+#             */
/*   Updated: 2023/10/22 11:03:41 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*initialize_tokens(t_minishell *mini, int token_count)
{
	int		counter;
	t_token	*token;

	counter = 0;
	token = malloc(token_count * sizeof(t_token));
	if (!token)
		return (malloc_error(mini, NULL), NULL);
	while (counter < token_count)
	{
		token[counter].indoublequote = 0;
		token[counter].inquote = 0;
		token[counter].token = NULL;
		token[counter].len = 0;
		token[counter].type = 0;
		counter++;
	}
	return (token);
}

t_type	get_type2(char *arg)
{
	if (arg[0] == ' ' || arg[0] == '\t' || arg[0] == '\n' || \
			arg[0] == '\v' || arg[0] == '\f' || arg[0] == '\r')
		return (WHITESPACE);
	else if (arg[0] == '<' && arg[1] == '<')
		return (HERE_DOC);
	else if (arg[0] == '>' && arg[1] == '>')
		return (APPEND);
	else if (arg[0] == '<')
		return (REDIRECT_INPUT);
	else if (arg[0] == '>')
		return (REDIRECT_OUTPUT);
	return (OTHER);
}

t_type	get_type(char *arg)
{
	if (ft_isdigit(arg[0]))
		return (DIGIT);
	else if (ft_isalpha(arg[0]))
		return (CHAR);
	else if (arg[0] == '\'')
		return (SINGLE_QUOTE);
	else if (arg[0] == '\"')
		return (DOUBLE_QUOTE);
	else if (arg[0] == '|')
		return (PIPE);
	else if (arg[0] == '$')
		return (DOLLAR_SIGN);
	else if (arg[0] == '=')
		return (EQUAL);
	return (get_type2(arg));
}

/*
// this is for types that usually are not by themselves, 
only adding a count after the entire sequence of characters

// this skips single characters that should be handled individually
*/
int	count_tokens(char *arg)
{
	t_type	type;
	int		count;

	count = 0;
	while (arg[0])
	{
		type = get_type(arg);
		if ((type == DOLLAR_SIGN && !ft_isalnum(arg[1]) && arg[1] != '?') || type == SINGLE_QUOTE || \
		type == DOUBLE_QUOTE || type == REDIRECT_INPUT || \
		type == REDIRECT_OUTPUT || type == EQUAL || \
		type == PIPE)
		{
			arg++;
			count++;
		}
		else if (type == APPEND || type == HERE_DOC)
		{
			arg += 2;
			count++;
		}
		else if (type == OTHER)
		{
			while (type == OTHER)
			{
				arg++;
				type = get_type(arg);
			}
			count++;
		}
		else if (type == CHAR)
		{
			while (type == CHAR)
			{
				arg++;
				type = get_type(arg);
			}
			count++;
		}
		else if (type == DIGIT)
		{
			while (type == DIGIT)
			{
				arg++;
				type = get_type(arg);
			}
			count++;
		}
		else if (type == WHITESPACE)
		{
			while (type == WHITESPACE)
			{
				arg++;
				type = get_type(arg);
			}
			count++;
		}
		else if ((type == DOLLAR_SIGN && ft_isalnum(arg[1]) || \
				type == DOLLAR_SIGN && arg[1] == '?'))
		{
			arg++;
			type = get_type(arg);
			while(type == CHAR || type == DIGIT)
			{
				arg++;
				type = get_type(arg);
			}
			count++;
		}
	}
	return (count);
}

int	get_inquote(t_token *token, char *arg, char *new, int len_to_skip)
{
	int		i;
	int		len;
	t_type	type;
	t_type	quote_type;
	
	arg += len_to_skip;
	quote_type = get_type(arg);
	arg++;
	len++;
	type = get_type(arg);
	while (type != quote_type)
	{
		if (quote_type == DOUBLE_QUOTE && type == DOLLAR_SIGN) // TODO: do DB_Q exception with *new
		{
			
		}
		type = get_type(arg);
	}
}

// returns -1 in case of error, len to skip otherwise
int	get_token(t_minishell *mini, t_token *token, char *arg, int len_to_skip)
{
	char	*new;
	t_type	type;
	int		len;
	int		i;

	if (arg[0] == '\0')
		return (0);
	arg += len_to_skip;
	new = ft_calloc(ft_strlen(&arg[0]), sizeof(char));
	if (!new)
		return (malloc_error(mini, NULL), -1);
	len = 0;
	i = 0;
	type = get_type;
	if ((type == DOLLAR_SIGN && !ft_isalnum(arg[1]) && arg[1] != '?') || type == SINGLE_QUOTE || \
		type == DOUBLE_QUOTE || type == REDIRECT_INPUT || \
		type == REDIRECT_OUTPUT || type == EQUAL || \
		type == PIPE)
	{
		if (type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
		{
			return (get_inquote(token, arg, new, len_to_skip));
		}
		new[0] = arg[0];
		arg++;
		len++;
	}
	else if (type == APPEND || type == HERE_DOC)
	{
		while(len < 2)
		{
			new[i++] =  arg[0];
			arg++;
			len++;
		}
	}
	else if (type == OTHER)
	{
		while (type == OTHER && arg)
		{
			token->token[i++] = arg[0];
			arg++;
			len++;
			type = get_type(arg);
		}
	}
	else if (type == CHAR)
	{
		while (type == CHAR && arg)
		{
			token->token[i++] = arg[0];
			arg++;
			len++;
			type = get_type(arg);
		}
	}
	else if (type == DIGIT)
	{
		while (type == DIGIT && arg)
		{
			token->token[i++] = arg[0];
			arg++;
			len++;
			type = get_type(arg);
		}
	}
	else if (type == WHITESPACE)
	{
		while (type == WHITESPACE && arg)
		{
			token->token[i++] = arg[0];
			arg++;
			len++;
			type = get_type(arg);
		}
	}
	else if ((type == DOLLAR_SIGN && ft_isalnum(arg[1]) || \
			type == DOLLAR_SIGN && arg[1] == '?'))
	{
		arg++;
		len++;
		if (arg[0] == '?')
		{
			arg++;
			len++;
			//TODO: make sure this else if works properly
		}
		else
		{
			type = get_type(arg);
			while(type == CHAR || type == DIGIT)
			{
				arg++;
				type = get_type(arg);
			}
		}
	}
	token->token = new;
	new = NULL;
	token->len = len;
	return (len);
}

t_token	*tokenize(t_minishell *mini, const char *arg)
{
	t_token	*tokens;
	int		token_count;
	int		i;
	int		len_to_skip;

	i = -1;
	len_to_skip = 0;
	token_count = count_tokens(arg);
	tokens = initialize_tokens(mini, token_count);
	printf("%d\n", token_count);
	while (++i < token_count)
	{
		len_to_skip += get_token(mini, &tokens[i], arg, len_to_skip); // TODO: review this function, may not be the best option
	}
	return (tokens);
}