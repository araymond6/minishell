#include "../include/minishell.h"

int	initialize_s_cmd(t_minishell *mini)
{
	int	n;

	n = 0;
	mini->s_cmd->path = NULL;
	mini->s_cmd->cmd_arg = NULL;
	mini->s_cmd->pids = ft_calloc(mini->cmd_n, sizeof(pid_t));
	if (!mini->s_cmd->pids)
		return(1);
	mini->s_cmd->narg = 0;
	mini->s_cmd->fd_stdin = dup(STDIN_FILENO);
	mini->s_cmd->fd_stdout = dup(STDOUT_FILENO);
	return(0);
}
