/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:16:11 by araymond          #+#    #+#             */
/*   Updated: 2023/11/07 11:10:46 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_pipe(char *arg, int *i, int *temp, t_type type)
{
	while (*temp >= 0)
	{
		type = get_type(&arg[*temp]);
		if (type != WHITESPACE && type != PIPE) 
			break ;
		else if (type == PIPE)
			return (1);
		else
			(*temp)--;
	}
	if (!arg[*i + 1] || arg[0] == '|' || *temp == -1)
		return (1);
	*temp = *i + 1;
	while (arg[*temp])
	{
		type = get_type(&arg[*temp]);
		if (type != WHITESPACE && type != PIPE)
			break ;
		else if (type == PIPE || arg[*temp] == 0)
			return (1);
		else 
			(*temp)++;
	}
	return (0);
}

static int	quote_check(t_minishell *mini, char *arg, int *i)
{
	if (arg[*i] == '\'')
	{
		(*i)++;
		while (arg[*i] != '\'')
			(*i)++;
	}
	else if (arg[*i] == '\"')
	{
		(*i)++;
		while (arg[*i] != '\"')
			(*i)++;
	}
}

int	pipe_parsing(t_minishell *mini, char *arg)
{
	int		i;
	int		temp;
	t_type	type;

	i = 0;
	type = 0;
	while (arg[i])
	{
		if (arg[i] == '|')
		{
			temp = i - 1;
			if (check_pipe(arg, &i, &temp, type) == 1)
				return (parsing_error(mini), 1);
		}
		else if (arg[i] == '\'' || arg[i] == '\"')
			quote_check(mini, arg, &i);
		i++;
	}
	return (0);
}

void	read_input(t_minishell *mini)
{
	while (1)
	{
		signal_reset(mini);
		mini->arg = readline("minishell % ");
		if (mini->arg == NULL)
			break ;
		add_history(mini->arg);
		if (mini->arg[0] == '\0' || whitespace_check(mini->arg) == 1
			|| pipe_parsing(mini, mini->arg) == 1)
		{
			free(mini->arg);
			continue ;
		}
		mini->arg = heredoc_substitution(mini, mini->arg);
		mini->token = tokenize(mini, mini->arg);
		if (!mini->token)
		{
			clear_mini(mini);
			continue ;
		}
		set_heredoc_flag(mini);
		if (mini->token)
			time_to_execute(mini);
		clear_mini(mini);
	}
}
