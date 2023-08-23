/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:29:56 by araymond          #+#    #+#             */
/*   Updated: 2023/08/23 16:47:24 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_mini(t_minishell *mini)
{
	
}

void	initialize_mini(t_minishell *mini)
{
	ft_bzero(mini, sizeof(t_minishell));
}