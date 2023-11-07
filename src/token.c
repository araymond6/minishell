/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:18:39 by araymond          #+#    #+#             */
/*   Updated: 2023/11/07 13:21:05 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*initialize_tokens(t_minishell *mini, int token_count)
{
	int		counter;
	t_token	*token;

	counter = 0;
	mini->token_count = token_count;
	token = malloc(token_count * sizeof(t_token));
	if (!token)
		return (malloc_error(mini, NULL), NULL);
	while (counter < token_count)
	{
		token[counter].inquote = 0;
		token[counter].token = NULL;
		token[counter].type = 0;
		token[counter].cmd_n = 0;
		counter++;
	}
	return (token);
}

t_type	get_type(char *arg)
{
	if (arg[0] == '\'')
		return (SINGLE_QUOTE);
	else if (arg[0] == '\"')
		return (DOUBLE_QUOTE);
	else if (arg[0] == '|')
		return (PIPE);
	else if (arg[0] == '$' && (arg[1] == '?' || arg[1] == '_' || \
			ft_isalnum(arg[1]) || arg[1] == '\'' || arg[1] == '\"'))
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

char	*get_exit_code(t_minishell *mini)
{
	char	*new;

	new = ft_itoa(mini->exit_code);
	if (!new)
		return (malloc_error(mini, NULL), NULL);
	return (new);
}

t_token	*tokenize(t_minishell *mini, char *arg)
{
	t_token	*tokens;
	int		token_count;

	mini->cmd_n = 1;
	token_count = count_tokens(mini, arg);
	if (token_count == -1)
		return (NULL);
	tokens = initialize_tokens(mini, token_count);
	if (get_tokens(mini, tokens, arg) == 1)
		return (parsing_error(mini), NULL);
	mini->token = tokens;
	if (redir_parsing2(mini))
		return (parsing_error(mini), NULL);
	return (tokens);
}
