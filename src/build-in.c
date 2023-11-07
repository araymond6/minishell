/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:17:26 by araymond          #+#    #+#             */
/*   Updated: 2023/11/06 16:35:29 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if (ft_strncmp(mini->s_cmd->cmd_arg[0], "echo", 5) == 0)
		return (ft_echo(mini->s_cmd));
	else if (ft_strncmp(mini->s_cmd->cmd_arg[0], "cd", 3) == 0)
		return (ft_cd(mini, mini->s_cmd));
	else if (ft_strncmp(mini->s_cmd->cmd_arg[0], "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(mini->s_cmd->cmd_arg[0], "export", 7) == 0)
		return (ft_export(mini));
	else if (ft_strncmp(mini->s_cmd->cmd_arg[0], "env", 4) == 0)
		return (ft_env(mini));
	else if (ft_strncmp(mini->s_cmd->cmd_arg[0], "unset", 6) == 0)
		return (ft_unset(mini));
	else if (ft_strncmp(mini->s_cmd->cmd_arg[0], "exit", 5) == 0)
		ft_exit(mini);
	return (0);
}
