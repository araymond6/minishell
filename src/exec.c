#include "../include/minishell.h"

// check if it<s a build0in or not and execute it
int	execute_cmd_buildin(t_minishell *mini)
{
	int exit_code;
	if (isbuildin(mini->s_cmd->cmd_arg[0]) == 0)
	{
		exit_code = execute_buildin(mini);
		exit(exit_code);
	}
	else
	{
		
		if (execve(mini->s_cmd->path, mini->s_cmd->cmd_arg, NULL) == -1)
		{
			free_scmd(mini->s_cmd);
			return (message_perror("EXECVE"));
		}
	}
	return (0);
}

// parent side of the process
int	parent(t_cmd *cmd)
{
	int originalStdin; 
	
	originalStdin = dup(STDIN_FILENO);
	close(cmd->pipe_fd[1]);
	if (cmd->prev->cmd != NULL)
	{
		if (dup2(cmd->prev->pipe_fd[0], STDIN_FILENO) == -1)
		{
			close(cmd->pipe_fd[0]);
			exit(EXIT_FAILURE);
		}
	}
	if (cmd->prev->cmd != NULL)
		close(cmd->prev->pipe_fd[0]);
	if (cmd->next->cmd == NULL)
		close(cmd->pipe_fd[0]);
	if (dup2(originalStdin, STDIN_FILENO) == -1) 
        return(message_perror("Error restoring stdin"));
	return (0);
}

// child side of the process - make the execution
int	child(t_minishell *mini)
{
	int	i;

	i = 0;
	if (mini->s_cmd->prev->cmd != NULL)
		if (dup2(mini->s_cmd->prev->pipe_fd[0], STDIN_FILENO) == -1)
			return (close(mini->s_cmd->pipe_fd[0]), close(mini->s_cmd->pipe_fd[1]), EXIT_FAILURE);
	if (mini->s_cmd->next->cmd != NULL && mini->s_cmd->next)
		if (dup2(mini->s_cmd->pipe_fd[1], STDOUT_FILENO) == -1)
			return (close(mini->s_cmd->pipe_fd[0]), close(mini->s_cmd->pipe_fd[1]), EXIT_FAILURE);
	if (mini->s_cmd->prev->cmd != NULL)
		close(mini->s_cmd->prev->pipe_fd[0]);
	if (mini->s_cmd->next->cmd == NULL)
		close(mini->s_cmd->pipe_fd[0]);
	close(mini->s_cmd->pipe_fd[1]);
	if (mini->s_cmd->redir)
	{
		while (mini->s_cmd->redir[i])
		{
			change_inf(mini->s_cmd->redir[i], mini->s_cmd->file[i]);
			change_out(mini->s_cmd->redir[i], mini->s_cmd->file[i]);
			i++;
		}
	}
	return (execute_cmd_buildin(mini));
}

int forker(int n, int *pids, t_minishell *mini)
{
 	int i;

	i = 0;
	if (pipe(mini->s_cmd->pipe_fd) == -1)
		return (free_scmd(mini->s_cmd), message_perror("Pipe"));
	if(n > 0)
    {
        if ((pids[i] = fork()) < 0)
            return (free_scmd(mini->s_cmd), message_perror("Fork"));
        else if (pids[i] == 0)
        {
            child(mini);
			mini->s_cmd = mini->s_cmd->next;
        }
        else if(pids[i] > 0)
        {
            parent(mini->s_cmd);
			if(ft_strncmp(mini->s_cmd->cmd_arg[0], "cd", 3) == 0)
				ft_cd(mini->s_cmd);
			else if(ft_strncmp(mini->s_cmd->cmd_arg[0], "export", 7) == 0)
				ft_export(mini);
			else if(ft_strncmp(mini->s_cmd->cmd_arg[0], "unset", 6) == 0)
				ft_env(mini);
			else if(ft_strncmp(mini->s_cmd->cmd_arg[0], "exit", 5) == 0)
				ft_exit(mini);
			mini->s_cmd = mini->s_cmd->next;
            forker(n - 1, pids +1, mini);
        }
	}
	return(0);
}

// the processus
int	process(t_minishell *mini)
{
	pid_t *pids;
	int i;
	int n;  // mettre le nombre de process que je vas avoir 

	n = 0;
	i = 0;
	while(mini->cmd[n])
		n++;
	pids = ft_calloc(n, sizeof(pid_t));
	pids[i] = 1;
	while (mini->s_cmd->next)
		forker(n, pids, mini);
	i = 0;
	while(i < n)
	{
		waitpid(pids[i], &mini->s_cmd->status, 0);
		if (WEXITSTATUS(mini->s_cmd->status) == 1)
			message_perror("WEXITSTATUS");
			i++;;

	}
	return (0);
}


/*
Here doc avec des pipes
Cat avec des pipes et rien après
Cat avec rien après
ctrl+c ctrl+d
To many open file
*/
