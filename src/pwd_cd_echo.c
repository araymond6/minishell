/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:18:57 by araymond          #+#    #+#             */
/*   Updated: 2023/11/06 12:06:56 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(void)
{
	char	absolute_path[200];

	if (getcwd(absolute_path, 200) == NULL)
		return (message_perror("pwd :"));
	printf("%s\n", absolute_path);
	return (0);
}

int	ft_cd(t_minishell *mini, t_cmd *cmd)
{
	int		count ;
	char	*home;

	count = count_2darray(cmd->cmd_arg);
	if (count == 1)
	{
		home = check_env(mini, "HOME");
		if (chdir(home + 5) == -1)
		{
			if (home)
				free(home);
			home = NULL;
			return (message_perror("cd"));
		}
		free(home);
		home = NULL;
		return (0);
	}
	if (chdir(cmd->cmd_arg[1]) == -1)
		return (message_perror("cd"));
	return (0);
}

void	p_echo(char **str, int r, int n)
{
	int	i;

	(void) str;
	i = 0;
	while (str[r] != NULL)
	{
		while (str[r][i])
		{
			write(1, &str[r][i], 1);
			i++;
		}
		i = 0;
		if (str[++r])
			write(1, " ", 1);
	}
	if (n == 0 || n == 2)
		write(1, "\n", 1);
}

int	ft_echo(t_cmd *cmd)
{
	int	r;
	int	i;
	int	n;

	r = 1;
	i = 2;
	n = 0;
	if (!cmd->cmd_arg[r])
		return (printf("\n"), 0);
	while (ft_strncmp(cmd->cmd_arg[r], "-n", 2) == 0
		&& n != 2 && cmd->cmd_arg[r])
	{
		while (cmd->cmd_arg[r][i] == 'n')
			i++;
		if (cmd->cmd_arg[r][i] == 0)
		{
			r++;
			n = 1;
			i = 2;
		}
		else
			n = 2;
	}
	p_echo(cmd->cmd_arg, r, n);
	return (0);
}
