/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:08:01 by vst-pier          #+#    #+#             */
/*   Updated: 2023/09/22 19:58:23 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_pwd(t_cmd *cmd)
{
	char	absolute_path[200];

	if (getcwd(absolute_path, 200) == NULL)
		return (message_perror("pwd :"));
	printf("%s\n", absolute_path);
	return(0);
}
