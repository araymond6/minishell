/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:16:54 by araymond          #+#    #+#             */
/*   Updated: 2023/11/07 13:30:43 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_token_type3(t_minishell *mini, t_token *tokens, char *arg, int *i)
{
	int	error;

	error = 0;
	if (tokens->type == DOLLAR_SIGN)
	{
		if (arg[i[0] + 1] == '\'' || arg[i[0] + 1] == '\"')
		{
			i[0]++;
			return (2);
		}
		error = do_substitution(mini, tokens, arg, i);
	}
	return (error);
}

int	get_token_type2(t_minishell *mini, t_token *tokens, char *arg, int *i)
{
	int	rtn;

	if (tokens->type == APPEND || tokens->type == HERE_DOC)
	{
		tokens->token[i[1]++] = arg[i[0]++];
		tokens->token[i[1]++] = arg[i[0]++];
	}
	else if (tokens->type == PIPE)
	{
		i[0]++;
		mini->cmd_n++;
		return (2);
	}
	else if (tokens->type == STRING || tokens->type == SINGLE_QUOTE \
		|| tokens->type == DOUBLE_QUOTE)
	{
		rtn = get_token_str_loop(mini, tokens, arg, i);
		if (rtn == 1)
			return (1);
		if (rtn == 2)
			return (2);
	}
	else
		return (get_token_type3(mini, tokens, arg, i));
	return (0);
}

int	get_token_type(t_minishell *mini, t_token *tokens, char *arg, int *i)
{
	tokens->type = get_type(&arg[i[0]]);
	printf("c: %c\n", arg[i[0]]);
	if (tokens->type == DOLLAR_SIGN && mini->prev_heredoc == 1)
		tokens->type = STRING;
	if (tokens->type == WHITESPACE)
	{
		while (tokens->type == WHITESPACE && arg[i[0]])
		{
			i[0]++;
			tokens->type = get_type(&arg[i[0]]);
			if (mini->arg[i[0]] == '\0')
				return (2);
		}
		if (arg[i[0]])
			return (2);
		return (0);
	}
	else if (tokens->type == REDIRECT_INPUT || tokens->type == REDIRECT_OUTPUT)
	{
		tokens->token[i[1]] = arg[i[0]];
		i[0]++;
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
	t = 0;
	rtn = 0;
	while (arg[i[0]])
	{
		if (rtn != 2)
		{
			set_flag(mini, tokens[t]);
			tokens[t].token = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
			if (!tokens[t].token)
				return (malloc_error(mini, NULL), 1);
			i[1] = 0;
		}
		tokens[t].cmd_n = mini->cmd_n;
		rtn = get_token_type(mini, &tokens[t], arg, i);
		if (rtn == 1)
			return (1);
		if (rtn == 0)
			t++;
	}
	return (0);
}
