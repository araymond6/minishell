/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:30:27 by vst-pier          #+#    #+#             */
/*   Updated: 2023/08/07 12:37:51 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//function qui va assigner les chose en cas de >>
void	append_redirection(t_minishell *mini, int i, int j)
{
	create_tab_file(mini);
	assign_redir_values(mini, '4');
}