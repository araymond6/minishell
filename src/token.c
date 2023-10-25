/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:43:51 by araymond          #+#    #+#             */
/*   Updated: 2023/10/24 16:51:10 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
// this is for types that usually are not by themselves, 
only adding a count after the entire sequence of characters

// this skips single characters that should be handled individually
*/
int	count_token(char *arg)
{
	t_type	type;
	int		count;

	count = 0;
	while (arg[0])
	{
		type = get_token(arg);
		if (type == DOLLAR_SIGN || type == SINGLE_QUOTE || \
		type == DOUBLE_QUOTE || type == REDIRECT_INPUT || \
		type == REDIRECT_OUTPUT || type == EQUAL || \
		type == PIPE)
		{
			count++;
			arg++;
		}
		else if (type == APPEND || type == HERE_DOC)
		{
			arg += 2;
			count++;
		}
		else if (type == OTHER || type == CHAR || \
		type == DIGIT || type == WHITESPACE)
		{
			while (type == OTHER)
			{
				arg++;
				type = get_token(arg);
			}
			count++;
		}
	}
	return (count);
}

t_token	*initialize_token(int token_count)
{
	int		counter;
	t_token	*token;

	counter = 0;
	token = ft_calloc(token_count, sizeof(t_token));
	while (counter < token_count)
	{
		token[counter].indoublequote = 0;
		token[counter].inquote = 0;
		token[counter].token = NULL;
		token[counter].type = 0;
		counter++;
	}
	return (token)
}

t_type	get_token(char *arg)
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
	else if (arg[0] == ' ' || arg[0] == '\t' || arg[0] == '\n')
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

t_token	*tokenize(t_minishell *mini, char *arg)
{
	t_token	*tokens;
	int		token_count;

	token_count = count_token(arg);
	tokens = initialize_token(token_count);
	
}