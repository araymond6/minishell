/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerie <valerie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:30:21 by vst-pier          #+#    #+#             */
/*   Updated: 2023/09/11 16:45:53 by valerie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//count the nbr of redirection in the command line
int	redir_count(char *cmd)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '<')
		{
			count += 1;
			if (cmd[i + 1] == '<')
				i++;
		}
		else if (cmd[i] == '>')
		{
			count += 1;
			if (cmd[i + 1] == '>')
				i++;
		}
	}
	return (count);
}

//assign the number for the redirection and the name of the file
int	redirection(t_minishell *mini, int i, int j, char c)
{
	int	len;
	int	r;
	int	index;

	len = 0;
	r = 0;
	index = -1;
	if (!mini->s_cmd->file)
		mini->s_cmd->file = ft_calloc(mini->s_cmd->nredir + 1, sizeof(char *));
	if (!mini->s_cmd->redir)
		mini->s_cmd->redir = ft_calloc(mini->s_cmd->nredir + 1, sizeof(char));
	assign_redir_values(mini, c);
	if (mini->cmd[i][j] == ' ')
		j++;
	len = len_until_space(mini, i, j);
	while (mini->s_cmd->file[r])
		r++;
	mini->s_cmd->file[r] = ft_calloc(len + 1, sizeof(char));
	while (++index < len)
		mini->s_cmd->file[r][index] = mini->cmd[i][j + index];
	return (j + index);
}

//assign the number for the redirection
void	assign_redir_values(t_minishell *mini, char c)
{
	int	k;

	k = 0;
	while (mini->s_cmd->redir[k])
		k++;
	mini->s_cmd->redir[k] = c;
}

int	entry_redirection(t_minishell *mini, int i, int j)
{
	if (mini->cmd[i][j] == '<')
		j = redirection(mini, i, j + 1, '2');
	else if (mini->cmd[i][j] == ' ')
		j = redirection(mini, i, j + 1, '1');
	else
		j = redirection(mini, i, j, '1');
	return (j);
}

int	exit_redirection(t_minishell *mini, int i, int j)
{
	if (mini->cmd[i][j] == '>')
		j = redirection(mini, i, j + 1, '4');
	else if (mini->cmd[i][j] == ' ')
		j = redirection(mini, i, j + 1, '3');
	else
		j = redirection(mini, i, j, '3');
	return (j);
}
