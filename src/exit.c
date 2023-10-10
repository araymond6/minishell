#include "../include/minishell.h"



void	free_scmd(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp)
	{
		if (temp->redir)
			free(temp->redir);
		if (temp->cmd)
			free(temp->cmd);
		if (temp->path)
			free(temp->path);
		if (temp->cmd_arg)
			free_array(temp->cmd_arg);
		if (cmd->file)
			free_array(temp->file);
		temp = temp->next;
		free(cmd);
		cmd = temp;
	}
}

void	free_scmd_execve(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp)
	{
		if (temp->redir)
			free(temp->redir);
		if (temp->cmd)
			free(temp->cmd);
		if (temp->path)
			free(temp->path);
		if (temp->cmd_arg)
			free_array(temp->cmd_arg);
		if (cmd->file)
			free_array(temp->file);
		temp = temp->next;
		free(cmd);
		cmd = temp;
	}
}

void	ft_exit(t_minishell *mini)
{
	free_scmd(mini->s_cmd);
	mini->exit_code = 0;
	//assigner les code d'erreur
	exit_program(mini);
}
