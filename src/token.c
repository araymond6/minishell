/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:43:51 by araymond          #+#    #+#             */
/*   Updated: 2023/10/23 15:10:34 by marvin           ###   ########.fr       */
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
		token[counter].cmd_n = 0;
		counter++;
	}
	return (token);
}

t_type	get_type2(char *arg)
{
	
}

t_type	get_type(char *arg)
{
	if (arg[0] == '\'')
		return (SINGLE_QUOTE);
	else if (arg[0] == '\"')
		return (DOUBLE_QUOTE);
	else if (arg[0] == '|')
		return (PIPE);
	else if (arg[0] == '$')
		return (DOLLAR_SIGN);
	else if (arg[0] == ' ' || arg[0] == '\t' || arg[0] == '\n' || \
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
	return (STRING);
}

/*
// this is for types that usually are not by themselves, 
only adding a count after the entire sequence of characters

// this skips single characters that should be handled individually
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

// int	get_inquote(t_minishell *mini, t_token *token, char *arg, char *new)
// {
// 	int		i;
// 	int		len;
// 	char	*sub;
// 	t_type	type;
// 	t_type	quote_type;
	
// 	i = 0;
// 	quote_type = get_type(arg);
// 	sub = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
// 	if (!sub)
// 		return (free(new), -1);
// 	arg++;
// 	len++;
// 	type = get_type(arg);
// 	while (type != quote_type)
// 	{
// 		if (quote_type == DOUBLE_QUOTE && type == DOLLAR_SIGN) // TODO: do DB_Q exception with *new
// 		{
// 			len++;
// 			arg++;
// 			type = get_type(arg);
// 			while (type == DIGIT || type == LETTERS || \
// 				arg[0] == '_' || type == DOUBLE_QUOTE)
// 			{
// 				sub[i++] = arg[0];
// 				len++;
// 				arg++;	
// 				type = get_type(arg);
// 			}
// 			if (sub[0] != '\0')
// 			{
// 				sub = check_env(mini, sub);
// 				i = 0;
// 				if (sub)
// 				{
					
// 				}
// 			}
// 		}
// 		type = get_type(arg);
// 	}
// }

/*
	Coller ce qui est entre guillemet apres une chaine de caractères s'il n'y a pas d'espace
*/

char	*get_exit_code(t_minishell *mini)
{
	char	*new;

	new = ft_itoa(mini->exit_code);
	if (!new)
		return (malloc_error(mini, NULL), NULL);
	return (new);
}

int	new_substitution(t_minishell *mini, t_token *token, char *arg, char *new)
{
	int		len;
	char	*sub;
	char	*temp;
	int		i;

	len = 1;
	i = 0;
	arg++;
	sub = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	if (!sub)
		return (-1);
	while ((ft_isalnum(arg[0]) || arg[0] == '?' || arg[0] == '_') && arg[0])
	{
		sub[i] = arg[0];
		arg++;
		len++;
		i++;
		if ((arg[0] == '?' && i > 0) || sub[0] == '?')
			break ;
	}
	if (sub[0] == '\0')
		return (len);
	if (sub[0] == '?')
	{
		free(sub);
		sub = get_exit_code(mini);
		if (!sub)
			return (-1);
	}
	else
	{
		temp = sub;
		sub = check_env(mini, temp);
		if (!sub)
			return (-1);
		free(temp);
	}
	temp = new;
	new = ft_strjoin(new, sub); //TODO: make substitutions work with exit_code and the rest next
	free(temp);
	return (len);
}

// returns -1 in case of error, len to skip otherwise
int	get_token(t_minishell *mini, t_token *token, char *arg, int len)
{
	char	*new;
	t_type	type;
	t_type	quote_type;
	int		len;
	int		i;

	if (arg[0] == '\0')
		return (0);
	new = ft_calloc(ft_strlen(&arg[0]), sizeof(char));
	if (!new)
		return (malloc_error(mini, NULL), -1);
	len = 0;
	i = 0;
	type = get_type;
	if (type == WHITESPACE)
	{
		while (type == WHITESPACE && arg[0])
		{
			arg++;
			len++;
			type = get_type(arg);
		}
	}
	else if ((type == DOLLAR_SIGN && (arg[1] != '?' || arg[1] != '_' || !ft_isalnum(arg[1]))) || \
			type == REDIRECT_INPUT || type == REDIRECT_OUTPUT)
	{
		new[i++] =  arg[0];
		arg++;
		len++;
	}
	else if (type == PIPE)
	{
		arg++;
		len++;
	}
	else if (type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
	{
		quote_type = get_type(arg);
		arg++;
		len++;
		while (type != quote_type && arg[0])
		{
			new[i++] = arg[0];
			arg++;
			len++;
			type = get_type(arg);
			if (type == DOLLAR_SIGN && quote_type == DOUBLE_QUOTE \
			&& (arg[1] == '?' || arg[1] == '_' || ft_isalnum(arg[1])))
			{
				len += new_substitution(mini, arg, new, &i);
			}
		}
		arg++;
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
	else if ((type == DOLLAR_SIGN && ft_isalnum(arg[1]) || \
			type == DOLLAR_SIGN && arg[1] == '?') && token->indoublequote == 1)
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
			while(type == LETTERS || type == DIGIT)
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
	if (token_count == -1)
		return (NULL);
	tokens = initialize_tokens(mini, token_count);
	printf("%d\n", token_count);
	while (++i < token_count)
	{
		arg += get_token(mini, &tokens[i], arg); // TODO: review this function, may not be the best option
	}
	return (tokens);
}