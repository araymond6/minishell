/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:26:24 by valerie           #+#    #+#             */
/*   Updated: 2023/09/19 16:02:17 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_struct(t_cmd *cmd)
{
	while(cmd)
	{
		if(cmd->file)
		free_array(cmd->file);
		if(cmd->redir)
		free(cmd->redir);
		if(cmd->cmd)
		free(cmd->cmd);
		if(cmd->path)
		free(cmd->path);
		if(cmd->cmd_arg)
		free_array(cmd->cmd_arg);
		if(cmd->prev)
			free(cmd->prev);
		if(cmd->next)
			cmd = cmd->next;
		if(!(cmd->next))
			free(cmd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;

	(void) argc;
	(void) argv;
	mini = ft_calloc(1, sizeof(t_minishell));
	save_path(mini, envp);
	mini->arg = NULL;
	mini->cmd = ft_calloc(4, sizeof(char *));
	mini->cmd[0] = ft_calloc(28, sizeof(char));
	mini->cmd[0] = "< Makefile cat";
	mini->cmd[1] = ft_calloc(28, sizeof(char));
	mini->cmd[1] = "grep NAME";
	mini->cmd[2] = ft_calloc(28, sizeof(char));
	mini->cmd[2] = "wc";
	mini->cmd[3] = ft_calloc(1, sizeof(char));
	mini->cmd[3] = NULL;
	mini->s_cmd = NULL;
	create_list(mini);
	if(mini->path_envp)
		free_array(mini->cmd);
	//free les trucs a aurelia qui reste a free et sa structure
	process(mini->s_cmd);
	//free_struct(mini->s_cmd);
	
}