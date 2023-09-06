/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerie <valerie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:30:21 by vst-pier          #+#    #+#             */
/*   Updated: 2023/09/06 14:21:47 by valerie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//function qui compte le nb de redirection quil y aura
int	redir_count(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
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
		i++;
	}
	return (count);
}

//function qui va assigner les chose en cas de <
int	redirection1234(t_minishell *mini, int i, int j, char c)
{
	int	len;
	int	r;
	int	index;

	len = 0;
	r = 0;
	index = 0;
	create_redir_file(mini);
	assign_redir_values(mini, c);
	if (mini->cmd[i][j] == ' ')
		j++;
	len = len_until_space(mini, i, j);
	while (mini->struct_cmd->file[r])
		r++;
	mini->struct_cmd->file[r] = ft_calloc(len + 1, sizeof(char));
	while (index < len)
	{
		mini->struct_cmd->file[r][index] = mini->cmd[i][j + index];
		index++;
	}
	return (j + index);
}

//function qui malloc *redir(types redirections) **file(nom des fichiers) 
void	create_redir_file(t_minishell *mini)
{
	int	i;

	i = 0;
	if (!mini->struct_cmd->file)
		mini->struct_cmd->file = ft_calloc(mini->struct_cmd->nb_redir + 1, sizeof (char*));
	if (!mini->struct_cmd->redir)
		mini->struct_cmd->redir = ft_calloc(mini->struct_cmd->nb_redir + 1, sizeof(char));
}

//assigner dans char *redir la sorte de redirection
void	assign_redir_values(t_minishell *mini, char c)
{
	int	k;

	k = 0;
	while (mini->struct_cmd->redir[k])
		k++;
	mini->struct_cmd->redir[k] = c;
}

//gerer les redirection de type entre
int	entry_redirection(t_minishell *mini, int i, int j)
{
	if (mini->cmd[i][j] == '<')
		j = redirection1234(mini, i, j + 1, '2');
	else if (mini->cmd[i][j] == ' ')
		j = redirection1234(mini, i, j + 1, '1');
	else
		j = redirection1234(mini, i, j, '1');
	return (j);
}

//gerer les redirection de type sortie
int	exit_redirection(t_minishell *mini, int i, int j)
{
	if (mini->cmd[i][j] == '>')
		j = redirection1234(mini, i, j + 1, '4');
	else if (mini->cmd[i][j] == ' ')
		j = redirection1234(mini, i, j + 1, '3');
	else
		j = redirection1234(mini, i, j, '3');
	return (j);
}
