/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:15 by araymond          #+#    #+#             */
/*   Updated: 2023/08/01 14:43:49 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/parsing.h"

void	save_path(t_minishell *mini, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if(ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			mini->path_envp = ft_calloc(ft_strlen(envp[i] - 4), sizeof(char));
			mini->path_envp = envp[i] + 5;
		}
		i++;		
	}
}

int main(int argc, char **argv, char **envp)
{
	t_minishell mini;

	ft_bzero(&mini, sizeof(mini));
	save_path(&mini, envp);
	read_input(&mini);
}
