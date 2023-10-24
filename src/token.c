/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:43:51 by araymond          #+#    #+#             */
/*   Updated: 2023/10/24 11:26:53 by araymond         ###   ########.fr       */
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

// returns -1 in case of error
int	new_substitution(t_minishell *mini, t_token *tokens, char *arg, int *i)
{
	int		len;
	char	*sub;
	char	*temp;
	int		j;

	len = 1;
	i = 0;
	arg++;
	sub = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	if (!sub)
		return (malloc_error(mini, NULL), -1);
	while ((ft_isalnum(arg[0]) || arg[0] == '?' || arg[0] == '_') && arg[0])
	{
		sub[j] = arg[0];
		arg++;
		len++;
		j++;
		if ((arg[0] == '?' && i > 0) || sub[0] == '?')
			break ;
	}
	if (sub[0] == '\0')
		return (free(sub), len);
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
		free(temp);
		if (!sub)
			return (-1);
	}
	temp = tokens->token;
	tokens->token = ft_strjoin(temp, sub); //TODO: make substitutions work with exit_code and the rest next
	free(temp);
	free(sub);
	if (!tokens->token)
		return (malloc_error(mini, NULL), -1);
	return (len);
}

int	type_check(t_minishell *mini, t_token *tokens, char *arg, int *i)
{
	if (tokens->type == WHITESPACE)
	{
		while (tokens->type == WHITESPACE && arg[0])
		{
			arg++;
		}
	}
	else if ((tokens->type == DOLLAR_SIGN && (arg[1] != '?' || arg[1] != '_' || !ft_isalnum(arg[1]))) || \
			tokens->type == REDIRECT_INPUT || tokens->type == REDIRECT_OUTPUT)
	{
		tokens->token[(*i)] = arg[0];
		arg++;
		return (1);
	}
	else if (tokens->type == PIPE)
	{
		arg++;
		mini->cmd_n++;
		tokens->cmd_n = mini->cmd_n;
	}
	return (0);
}

int	quote_check(t_minishell *mini, t_token *tokens, char *arg, int *i)
{
	t_type	quote_type;
	t_type	type;

	type = tokens->type;
	if (type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
	{
		quote_type = get_type(arg);
		arg++;
		if (quote_type == SINGLE_QUOTE)
			tokens->inquote = 1;
		else
			tokens->indoublequote = 1;
		while (type != quote_type && arg[0])
		{
			tokens->token[(*i)++] = arg[0];
			arg++;
			type = get_type(arg);
			if (type == DOLLAR_SIGN && quote_type == DOUBLE_QUOTE \
			&& (arg[1] == '?' || arg[1] == '_' || ft_isalnum(arg[1])))
			{
				if (new_substitution(mini, tokens, arg, &i) == -1)
					return (malloc_error(mini, NULL), -1);
			}
		}
		arg++;
	}
}

// returns -1 in case of error, len to skip otherwise
int	get_tokens(t_minishell *mini, t_token *tokens, char *arg)
{
	t_type	type;
	int		t;
	int		i;

	t = 0;
	i = 0;
	tokens[t].cmd_n = mini->cmd_n;
	if (arg[0] == '\0')
		return (0);
	tokens->token = ft_calloc(ft_strlen(&arg[0]), sizeof(char));
	if (!tokens->token)
		return (malloc_error(mini, NULL), -1);
	while (arg[0])
	{
		tokens[t].type = get_type;
		if (type_check(mini, &tokens[t], arg, &i))
		{
			t++;
			continue ;
		}
		if (quote_check(mini, &tokens[t], arg, &i) == -1)
			return (-1);
		if (type == APPEND || type == HERE_DOC)
		{
			while (iterator < 2)
			{
				tokens->token[i++] = arg[0];
				arg++;
			}
		}
		else if (type == STRING)
		{
			while (type == STRING && arg)
			{
				tokens->token[i++] = arg[0];
				arg++;
				type = get_type(arg);
			}
			if (type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
			{
				quote_type = get_type(arg);
				arg++;
				while (type != quote_type && arg[0])
				{
					tokens->token[i++] = arg[0];
					arg++;
					type = get_type(arg);
				}
				if (type != quote_type)
					return (-1);
				arg++;
			}
		}
		else if ((type == DOLLAR_SIGN && ft_isalnum(arg[1]) || \
				type == DOLLAR_SIGN && arg[1] == '?') && tokens->inquote != 1)
		{
			arg++;
			if (arg[0] == '?')
			{
				arg++;
				//TODO: make sure this else if works properly
			}
			else
			{
				type = get_type(arg);
				while()
				{
					arg++;
					type = get_type(arg);
				}
			}
		}
	}
	return (0);
}

t_token	*tokenize(t_minishell *mini, const char *arg)
{
	t_token	*tokens;
	int		token_count;
	int		i;

	mini->cmd_n = 1;
	i = -1;
	token_count = count_tokens(mini, arg);
	if (token_count == -1)
		return (NULL);
	tokens = initialize_tokens(mini, token_count);
	printf("%d\n", token_count);
	if (get_tokens(mini, tokens, arg, 0) == -1) // TODO: review this function, may not be the best option
		return (parsing_error(mini), NULL);
	return (tokens);
}