#include "../include/minishell.h"

int	null_command2(t_minishell *mini, int n)
{
	int i;

	i = 0;
	manual_redirection(mini, n);
	if (dup2(mini->s_cmd->fd_stdout, STDOUT_FILENO) == -1)
		message_perror("Error restoring stdout");
	if (dup2(mini->s_cmd->fd_stdin, STDIN_FILENO) == -1)
		message_perror("Error restoring stdin");
	clear_s_cmd(mini->s_cmd);//
}

//les build_in nont jamais besoin d<aller lire le resultat de la commande avant donc pas besoin de changer le stdin pour le pipe
void exec_buildin2(t_minishell *mini, int n)
{
	int i;

	i = 0;
	if(n < mini->total_cmd)
	{
		if (dup2(mini->s_cmd->pipe[2 * (n - 1) + 1], STDOUT_FILENO) == -1)
			message_perror("Impossible to write in the pipe");
	}
		manual_redirection(mini, n);
		execute_buildin(mini);
		if (dup2(mini->s_cmd->fd_stdout, STDOUT_FILENO) == -1)
			message_perror("Impossible to reassign the STDOUT");
		if (dup2(mini->s_cmd->fd_stdin, STDIN_FILENO) == -1)
			message_perror("Impossible to reassign the STDIN");
		clear_s_cmd(mini->s_cmd);
	return (0);
}