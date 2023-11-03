/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:18:44 by araymond          #+#    #+#             */
/*   Updated: 2023/11/03 18:27:15 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_substitute(t_minishell *mini, char *sub)
{
	char	*temp;

	if (sub[0] == '?')
	{
		free(sub);
		sub = get_exit_code(mini);
		if (!sub)
			return (malloc_error(mini, NULL), NULL);
	}
	else
	{
		temp = sub;
		sub = check_env(mini, temp);
		if (!sub)
			return (malloc_error(mini, NULL), NULL);
		free(temp);
	}
	return (sub);
}

static char	*sub_loop(t_minishell *mini, char *arg, int *i)
{
	char	*sub;
	int		j;

	j = 0;
	sub = ft_calloc(ft_strlen(&arg[i[0]]) + 1, sizeof(char));
	if (!sub)
		return (malloc_error(mini, NULL), NULL);
	while ((ft_isalnum(arg[i[0]]) || arg[i[0]] == '?'
			|| arg[i[0]] == '_') && arg[i[0]])
	{
		sub[j++] = arg[i[0]++];
		if ((arg[i[0]] == '?' && i > 0) || sub[0] == '?')
			break ;
	}
	return (get_substitute(mini, sub));
}

int	new_substitution(t_minishell *mini, t_token *tokens, char *arg, int *i)
{
	char	*sub;
	char	*temp;
	int		j;

	j = 0;
	i[0]++;
	sub = sub_loop(mini, arg, i);
	if (sub == NULL)
		return (1);
	if (ft_strchr(sub, '='))
	{
		while (sub[j] != '=')
			j++;
		j++;
	}
	temp = tokens->token;
	tokens->token = ft_strjoin(temp, &sub[j]);
	free(temp);
	free(sub);
	if (!tokens->token)
		return (malloc_error(mini, NULL), 1);
	tokens->type = STRING;
	return (0);
}
