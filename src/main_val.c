/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:26:24 by valerie           #+#    #+#             */
/*   Updated: 2023/09/21 16:57:34 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//TODO here doc quand il y a des pipes
int	x_comm(t_minishell *mini)
{

	mini->s_cmd = NULL;
	create_list(mini);
	process(mini->s_cmd);
	free(mini->s_cmd);
	free(mini);
}
