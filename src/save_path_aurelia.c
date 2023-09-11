/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path_aurelia.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerie <valerie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:15 by araymond          #+#    #+#             */
/*   Updated: 2023/09/11 15:57:24 by valerie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	save_path(t_minishell *mini, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			mini->path_envp = ft_calloc(ft_strlen(envp[i] - 4), sizeof(char));
			mini->path_envp = envp[i] + 5;
		}
		i++;
	}
}
