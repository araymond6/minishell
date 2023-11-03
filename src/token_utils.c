/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:18:32 by araymond          #+#    #+#             */
/*   Updated: 2023/11/03 17:43:18 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_flag(t_minishell *mini, t_token tokens)
{
	if (tokens.type == HERE_DOC)
		mini->prev_heredoc = 1;
	else
		mini->prev_heredoc = 0;
}

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
			type = get_type(&arg[*i]);
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
		if ((tokens->type == DOLLAR_SIGN && arg[i[0] + 1] != '\"') \
			&& quote_type == DOUBLE_QUOTE)
		{
			error = do_substitution(mini, tokens, arg, i);
			if (error == 1)
				return (error);
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
			tokens->inquote = 1;
			if (quotestr_loop(mini, tokens, arg, i))
				return (1);
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
