/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:24:14 by araymond          #+#    #+#             */
/*   Updated: 2023/08/24 14:46:19 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parsing_error(t_minishell *mini)
{
	if (write(STDOUT_FILENO, "error\n", 15) == -1)
		parse_exit(mini);
}
