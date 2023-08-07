/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:30:14 by vst-pier          #+#    #+#             */
/*   Updated: 2023/08/07 12:41:38 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//function qui va assigner les chose en cas de >
void	std_exit_redirection(t_minishell *mini, int i, int j)
{
	create_tab_file(mini);
	assign_redir_values(mini, '3');
}