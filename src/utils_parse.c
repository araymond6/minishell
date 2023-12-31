/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:15:41 by araymond          #+#    #+#             */
/*   Updated: 2023/11/07 13:54:30 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_path(t_minishell *mini)
{
	int		i;
	char	*path;

	i = -1;
	path = "PATH=";
	while (mini->envp[++i])
	{
		if (!ft_strncmp(path, mini->envp[i], ft_strlen(path)))
		{
			return (mini->envp[i]);
		}
	}
	return (NULL);
}

// zeroes t_minishell and set envp and signal handlers
void	initialize_mini(t_minishell *mini, char **envp)
{
	ft_bzero(mini, sizeof(t_minishell));
	mini->envp = envp;
	mini->path = get_path(mini);
}

void	clear_mini(t_minishell *mini)
{
	int	i;

	i = 0;
	if (mini->arg)
	{
		free(mini->arg);
		mini->arg = NULL;
	}
	if (mini->token)
	{
		while (i < mini->token_count)
		{
			if (mini->token[i].token)
				free(mini->token[i++].token);
		}
		free(mini->token);
		mini->token = NULL;
	}
	if (mini->heredoc_flag)
	{
		free(mini->heredoc_flag);
		mini->heredoc_flag = NULL;
	}
	mini->heredoc_count = 0;
	mini->sigint = 0;
}

// sets error code to 1, prints error message 
// and frees array if deemed necessary
void	malloc_error(t_minishell *mini, char **to_free)
{
	mini->exit_code = 1;
	if (to_free)
	{
		free_array(to_free);
		to_free = NULL;
	}
	printf("malloc error\n");
}

int	do_substitution(t_minishell *mini, t_token *tokens, char *arg, int *i)
{
	int	size;
	int	type;

	if (new_substitution(mini, tokens, arg, i) == 1)
		return (1);
	size = ft_strlen(tokens->token);
	i[1] = size;
	tokens->token = ft_realloc(tokens->token, size,
			size + ft_strlen(&arg[i[0]]) + 1);
	if (!tokens->token)
		return (malloc_error(mini, NULL), 1);
	type = get_type(&arg[i[0]]);
	tokens->type = STRING;
	if (type == STRING || type == SINGLE_QUOTE \
	|| type == DOUBLE_QUOTE || type == DOLLAR_SIGN || \
	whitespace_check(&mini->arg[i[0]]))
	{
		return (2);
	}
	return (0);
}
