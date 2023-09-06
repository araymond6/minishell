/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarsign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:44:50 by araymond          #+#    #+#             */
/*   Updated: 2023/09/06 14:02:27 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	count_sub_env(t_minishell *mini, char *arg)
{
	int	i;
	int *new;

	i = 0;
	if (!arg || arg[0] == '\0')
		return ;
	new = check_env(mini, arg);
	if (!new)
		return ;
	while (new[i] )
	{
		
	}
}

// substitutes the $ARG in mini->arg[i] and puts it into mini->cmd[c][j]
void	sub_dollar(t_minishell *mini, int *i, int *j)
{
	
}

// counts how many characters to remove and checks env to see \
how many characters to add to it
void	count_sub_dollar(t_minishell *mini, int *i)
{
	char	*arg;
	int		j;

	arg = ft_calloc((ft_strlen(&mini->arg[*i]) + 1), sizeof(char));
	if (!arg)
		malloc_error(mini);
	(*i)++;
	mini->parse.sub--;
	while (mini->arg[*i])
	{
		if (!ft_isalnum(mini->arg[*i]))
			break ;
		arg[j++] = mini->arg[(*i)++];
		mini->parse.sub--;
	}
	if (mini->arg[*i] == '?' && mini->arg[*i - 1] == '$')
	{
		mini->parse.sub += ft_strlen(ft_atoi(mini->exit_code));
		free(arg);
		return ;
	}
	count_sub_env(mini, arg);
	if (mini->arg[*i] == '$')
		count_sub_dollar(mini, i);
	free(arg);
}
