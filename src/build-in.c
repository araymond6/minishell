/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerie <valerie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:39:50 by valerie           #+#    #+#             */
/*   Updated: 2023/09/11 11:49:49 by valerie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//this function check if command is a buildin to program
int	isbuildin(char *isbuildin)
{
	if (ft_strncmp(isbuildin, "echo", 4) == 0
		|| ft_strncmp(isbuildin, "cd", 2) == 0
		|| ft_strncmp(isbuildin, "pwd", 3) == 0
		|| ft_strncmp(isbuildin, "export", 6) == 0
		|| ft_strncmp(isbuildin, "unset", 5) == 0
		|| ft_strncmp(isbuildin, "env", 3) == 0
		|| ft_strncmp(isbuildin, "exit", 4) == 0)
		return (0);
	return (1);
}

int	execute_buildin(void)
{
	return (0);
}
