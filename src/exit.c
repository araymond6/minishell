#include "../include/minishell.h"

void	free_scmd(t_cmd *cmd)
{
	//TODO remettre a jour ave la struc au complet
	if (cmd)
	{
		if(cmd->path)
		{
			free(cmd->path);
			cmd->redir = NULL;
		}
		if(cmd->cmd_arg)
		{
			free_array(cmd->cmd_arg);
			cmd->cmd_arg = NULL;
		}
		if(cmd->pipe)
		{
			free(cmd->pipe);
			cmd->pipe = NULL;
		}
		if(cmd->status)
		{
			free(cmd->status);
			cmd->redir = NULL;
		}
		if(cmd->pids)
		{
			free(cmd->pids);
			cmd->pids = NULL;
		}
		close(cmd->fd_stdin);
		close(cmd->fd_stdout);
		cmd = NULL;
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

int free_exit(t_minishell *mini)
{
	free_scmd(mini->s_cmd);
	exit_program(mini);
	return(0);
}

int	ft_exit(t_minishell *mini)
{
	int			nb_arg;

	nb_arg = 0;
	while (mini->s_cmd->cmd_arg[nb_arg])
		nb_arg++;
	if (nb_arg == 1)
		free_exit(mini);
	if (nb_arg == 2)
	{
		if (is_valid_exit_code(mini) == 1)
			return (printf("Not a numeric argument\n"), 1);
		mini->exit_code = atol(mini->s_cmd->cmd_arg[1]);
		free_exit(mini);
	}
	else if (nb_arg > 2)
	{
		if (is_valid_exit_code(mini) == 0)
			return (printf("Too many arguments\n"), 1);
		free_exit(mini);
	}
	return (0);
}
