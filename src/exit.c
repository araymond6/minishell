#include "../include/minishell.h"

void	free_scmd(t_cmd *cmd)
{
	t_cmd	*temp;

	if (cmd)
	{
		free(cmd->prev);
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
}

int	is_valid_exit_code(t_minishell *mini)
{
	int	i;

	i = 0;
	if (mini->s_cmd->cmd_arg[1][0] == '+' || \
		mini->s_cmd->cmd_arg[1][0] == '-')
		i++;
	while (mini->s_cmd->cmd_arg[1][i])
	{
		if (mini->s_cmd->cmd_arg[1][i] >= '0' \
			&& mini->s_cmd->cmd_arg[1][i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_exit(t_minishell *mini)
{
	int			nb_arg;

	nb_arg = 0;
	while (mini->s_cmd->cmd_arg[nb_arg])
		nb_arg++;
	if (nb_arg == 1)
	{
		free_scmd(mini->s_cmd);
		exit_program(mini);
	}
	if (nb_arg == 2)
	{
		if (is_valid_exit_code(mini) == 1)
			return (printf("Not a numeric argument\n"), 1);
		mini->exit_code = atol(mini->s_cmd->cmd_arg[1]);
		free_scmd(mini->s_cmd);
		exit_program(mini);
	}
	else if (nb_arg > 2)
	{
		if (is_valid_exit_code(mini) == 0)
			return (printf("Too many arguments\n"), 1);
		free_scmd(mini->s_cmd);
		exit_program(mini);
	}
	return (0);
}
