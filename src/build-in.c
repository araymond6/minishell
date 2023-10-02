/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:39:50 by valerie           #+#    #+#             */
/*   Updated: 2023/10/02 14:36:11 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//this function check if command is a buildin to program
int	isbuildin(char *isbuildin)
{
	if (ft_strncmp(isbuildin, "echo", 5) == 0
		|| ft_strncmp(isbuildin, "cd", 3) == 0
		|| ft_strncmp(isbuildin, "pwd", 4) == 0
		|| ft_strncmp(isbuildin, "export", 7) == 0
		|| ft_strncmp(isbuildin, "unset", 6) == 0
		|| ft_strncmp(isbuildin, "env", 4) == 0
		|| ft_strncmp(isbuildin, "exit", 5) == 0)
		return (0);
	return (1);
}

int	execute_buildin(t_minishell *mini)
{
	//if(ft_strncmp(mini->s_cmd->cmd_arg[0], "echo", 4) == 0)
		//return (ft_echo(mini->s_cmd));
	if(ft_strncmp(mini->s_cmd->cmd_arg[0], "cd", 2) == 0)
		return (ft_cd(mini->s_cmd));
	else if(ft_strncmp(mini->s_cmd->cmd_arg[0], "pwd", 3) == 0)
		return (ft_pwd(mini->s_cmd));
	else if(ft_strncmp(mini->s_cmd->cmd_arg[0], "export", 6) == 0)
		return (ft_export(mini));
	else if(ft_strncmp(mini->s_cmd->cmd_arg[0], "env", 3) == 0)
		return (ft_env(mini));
	else if(ft_strncmp(mini->s_cmd->cmd_arg[0], "unset", 5) == 0)
		return (ft_unset(mini));
	//else if(ft_exit(mini->s_cmd->cmd_arg[0], "exit", 4) == 0)
		//ft_exit(mini->s_cmd);
	return (0);
}
