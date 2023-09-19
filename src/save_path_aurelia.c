/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_path_aurelia.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:15 by araymond          #+#    #+#             */
/*   Updated: 2023/09/19 13:46:09 by vst-pier         ###   ########.fr       */
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
			mini->path_envp = NULL;
			mini->path_envp = ft_calloc(ft_strlen(envp[i] - 4), sizeof(char));
			mini->path_envp = envp[i] + 5;
		}
		i++;
	}
}
