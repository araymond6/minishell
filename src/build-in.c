/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:39:50 by valerie           #+#    #+#             */
/*   Updated: 2023/09/26 13:30:54 by vst-pier         ###   ########.fr       */
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

int	execute_buildin(t_minishell *mini)
{
	if(ft_strncmp(mini->s_cmd->cmd_arg[0], "echo", 4) == 0)
		return (ft_echo(mini->s_cmd));
	if(ft_strncmp(mini->s_cmd->cmd_arg[0], "cd", 2) == 0)
		return (ft_cd(mini->s_cmd));
	else if(ft_strncmp(mini->s_cmd->cmd_arg[0], "pwd", 3) == 0)
		return (ft_pwd());
	//else if(ft_strncmp(mini->s_cmd->cmd_arg[0], "export", 6) == 0)
		//return (ft_export(mini->s_cmd));
	//else if(ft_strncmp(mini->s_cmd->cmd_arg[0], "env", 3) == 0)
		//return (ft_env(mini->s_cmd));
	//else if(ft_exit(mini->s_cmd->cmd_arg[0], "exit", 4) == 0)
		//ft_exit(mini->s_cmd);
	return (0);
}
