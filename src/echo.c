/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:49:34 by vst-pier          #+#    #+#             */
/*   Updated: 2023/09/26 15:33:56 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void p_echo(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] != 34 && str[i] != 39)        //faire en sorte dMimprimer ce qu<il y a entre "" ou ''
			printf("%c", str[i]);
		i++;
	}
}

int ft_echo(t_cmd *cmd)
{
	int i;

	i = 1;
	if(ft_strncmp(cmd->cmd_arg[1], "-n", 2) == 0)
		i++;
	while(cmd->cmd_arg[i] != NULL)
	{
		p_echo(cmd->cmd_arg[i]);
		i++;
		if(cmd->cmd_arg[i] != NULL)
			printf(" ");
	}
	if(ft_strncmp(cmd->cmd_arg[1], "-n", 2) != 0)
		printf("\n");
	return(1);
}