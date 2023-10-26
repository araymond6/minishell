#include "../include/minishell.h"

//initialize s_cmd
void	initialize_s_cmd(t_minishell *mini)
{
	int n;
	int pipes[2];

	n = 0;
	mini->s_cmd->path = NULL;
	mini->s_cmd->cmd_arg = NULL;
	mini->s_cmd->pids = ft_calloc(mini->cmd_n, sizeof(pid_t));
	printf("%d\n", mini->cmd_n);
	mini->s_cmd->pipe = ft_calloc(2 * (mini->cmd_n), sizeof(int));
	while(n < mini->cmd_n)
	{
		if (pipe(pipes) == -1)
		{
			free_scmd(mini->s_cmd);
			message_perror("Pipe");
		}
		mini->s_cmd->pipe[2 * n] = pipes[0];
		mini->s_cmd->pipe[(2 * n) - 1] = pipes[1];
		n++;
	}
	mini->s_cmd->narg = 0;
	mini->s_cmd->status = ft_calloc(mini->cmd_n, sizeof(int));
	mini->s_cmd->fd_stdin = dup(STDIN_FILENO);
	mini->s_cmd->fd_stdout = dup(STDOUT_FILENO);
	mini->s_cmd->pids[0] = 1;
}
