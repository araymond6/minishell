/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:08:01 by vst-pier          #+#    #+#             */
/*   Updated: 2023/09/29 11:15:33 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_pwd(void)
{
	char	absolute_path[200];

	if (getcwd(absolute_path, 200) == NULL)
		return (message_perror("pwd :"));
	printf("%s\n", absolute_path);
	return(0);
}

int ft_cd(t_cmd *cmd)
{
	if(chdir(cmd->cmd_arg[1])== -1)
		return(message_perror("cd : "));
	return(0);
}

int p_echo_next(char c, int q)
{
	if(c == 34 && q == 0)
		q = 1;
	else if(c == 39 && q == 0)
		q = 2;
	else if((c == 34 && q == 1) || (c == 39 && q == 2))
		q = 0;
	if(c != 34 && c != 39)
		printf("%c", c);
	else if(c == 34 && q == 2)
		printf("%c", c);
	else if(c == 39 && q == 1)
		printf("%c", c);
	return(q);
}

void p_echo(char **str, int r)
{
	int i;
	int q;

	q = 0;
	i = 0;
	
	while(str[r] != NULL)
	{
		while(str[r][i])
		{
			p_echo_next(str[r][i], q);
			i++;
		}
		r++;
		i = 0;
		if(str[r] != NULL)
			printf(" ");
	}
}

int ft_echo(t_cmd *cmd)
{
	int r;
	int i;
	int n;

	r = 1;
	i = 2;
	n = 0;
	while(ft_strncmp(cmd->cmd_arg[r], "-n", 2) == 0 && n != 2)
	{
		while(cmd->cmd_arg[r][i] == 'n')
			i++;
		if(cmd->cmd_arg[r][i] == 0)
		{
			r++;
			n = 1;
		}
		else
			n = 2;
		i = 2;
	}
	p_echo(cmd->cmd_arg, r);
	if(n == 0 || n == 2)
		printf("\n");
	return(1);
}
