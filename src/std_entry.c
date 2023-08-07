/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:30:21 by vst-pier          #+#    #+#             */
/*   Updated: 2023/08/07 13:20:16 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//function qui va assigner les chose en cas de <
int	std_entry_redirection(t_minishell *mini, int i, int j)
{		
	int len;
	int r;
	int index;

	len = 0;
	r = 0;
	index = 0;
	create_tab_file(mini);
	assign_redir_values(mini, '1');
	len = len_until_space(mini, i, j);
	while(mini->struct_cmd->file[r][0] != '\0')
		r++;
	mini->struct_cmd->file[r] = ft_calloc( len + 1, sizeof(char));
	while(index < len)	
	{
		mini->struct_cmd->file[r][index] = mini->cmd[i][j + index];
		index++;
	}
	return(j + index);
	
}