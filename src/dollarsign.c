/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarsign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 09:44:50 by araymond          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/29 11:13:16 by vst-pier         ###   ########.fr       */
=======
/*   Updated: 2023/09/29 11:35:42 by araymond         ###   ########.fr       */
>>>>>>> 97a785bc1f5a6126876d4b436930c703f0804005
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// adds to mini->parse.sub the c count if found
void	add_sub_env(t_minishell *mini, char *arg)
{
	int		i;
	char	*new;

	i = 0;
	if (!arg || arg[0] == '\0')
		return ;
	new = check_env(mini, arg);
	if (!new || new[0] == '\0')
		return ;
	while (new[i] != '=')
		i++;
	i++;
	while (new[i])
	{
		mini->parse.sub++;
		i++;
	}
	free(new);
}

//adds the substitution of the env var to mini->cmd
void	add_from_env(t_minishell *mini, int *j, char *arg)
{
	char	*new;
	int		k;

	k = 0;
	new = check_env(mini, arg);
	if (!new || new[0] == '\0' || !arg || arg[0] == '\0')
		return ;
	while (new[k] != '=')
		k++;
	k++;
	while (new[k])
		mini->cmd[mini->parse.c][(*j)++] = new[k++];
	free(new);
}

//exit_code exception
void	add_exitcode(t_minishell *mini, int *j, char *arg)
{
	int	k;

	k = -1;
	while (arg[++k])
	{
		mini->cmd[mini->parse.c][(*j)++] = arg[k];
	}
}
<<<<<<< HEAD

// substitutes the $ARG in mini->arg[i] and puts it into mini->cmd[c][j]
void	sub_dollar(t_minishell *mini, int *i, int *j)
{
	char	*arg;
	char	*exception;
	int		k;

	k = 0;
	arg = ft_calloc((ft_strlen(&mini->arg[*i]) + 1), sizeof(char));
	if (!arg)
		malloc_error(mini);
	(*i)++;
	while (mini->arg[*i])
	{
		if (!ft_isalnum(mini->arg[*i]))
			break ;
		arg[k++] = mini->arg[(*i)++];
	}
	if (mini->arg[*i] == '?' && mini->arg[*i - 1] == '$')
	{
		exception = ft_itoa(mini->exit_code);
		if (!exception)
			malloc_error(mini);
		add_exitcode(mini, j, exception);
		free(arg);
		return ;
	}
	add_from_env(mini, j, arg);
	if (mini->arg[*i] == '$')
		sub_dollar(mini, i, j);
	free(arg);
}

// counts how many characters to remove and checks env to see
//how many characters to add to it
void	count_sub_dollar(t_minishell *mini, int *i)
{
	char	*arg;
	char	*exception;
	int		j;

	j = 0;
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
		exception = ft_itoa(mini->exit_code);
		if (!exception)
		{
			free(arg);
			malloc_error(mini);
		}
		mini->parse.sub += ft_strlen(exception);
		free(arg);
		free(exception);
		return ;
	}
	add_sub_env(mini, arg);
	if (mini->arg[*i] == '$')
		count_sub_dollar(mini, i);
	free(arg);
}
=======
>>>>>>> 97a785bc1f5a6126876d4b436930c703f0804005
