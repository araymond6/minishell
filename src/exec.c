#include "../include/minishell.h"
// check if it<s a build0in or not and execute it
int execute_cmd_buildin(t_minishell *mini)
{
	int	exit_code;
	char *cmd;
	char **tab_path;
	int len;

	len = 0;
	if(ft_strlen(mini->s_cmd->cmd) == 0)
		exit(0);
	else if (isbuildin(mini->s_cmd->cmd) == 0)
	{
		exit_code = execute_buildin(mini);
		exit(exit_code);
	}
	else
	{
		cmd = ft_calloc(ft_strlen(mini->s_cmd->path) + 1, sizeof(char));
		if(cmd == NULL)
			return(free_scmd(mini->s_cmd), 1);
		ft_strlcpy(cmd, mini->s_cmd->path, ft_strlen(mini->s_cmd->path));
		while(mini->s_cmd->cmd_arg[len])
			len++;
		tab_path = ft_calloc(len + 1, sizeof(char*));
		if(tab_path == NULL)
			return(free(cmd), free_scmd(mini->s_cmd), 1);
		len = 0;
		while(mini->s_cmd->cmd_arg[len])
		{
			tab_path[len] = ft_calloc(ft_strlen(mini->s_cmd->cmd_arg[len]), sizeof(char));
			if(tab_path == NULL)
				return(free(cmd), free_array(tab_path), free_scmd(mini->s_cmd), 1);
			ft_strlcpy(tab_path[len], mini->s_cmd->cmd_arg[len], ft_strlen(mini->s_cmd->path));
			len++;
		}
		ft_strlcpy(cmd, mini->s_cmd->path, ft_strlen(mini->s_cmd->path));
		if (execve(cmd, tab_path, NULL) == -1)
		{
			free(cmd);
			free_array(tab_path);
			return (message_perror("EXECVE"));
		}
	}
	return (0);
}
// parent side of the process
int parent(t_cmd *cmd)
{
    int originalstdin;
    originalstdin = dup(STDIN_FILENO);
    close(cmd->fd[1]);
    if (cmd->prev->cmd != NULL)
    {
        if (dup2(cmd->prev->fd[0], STDIN_FILENO) == -1)
        {
            close(cmd->fd[0]);
            exit(EXIT_FAILURE);
        }
    }
    if (cmd->prev->cmd != NULL)
        close(cmd->prev->fd[0]);
    if (cmd->next->cmd == NULL)
        close(cmd->fd[0]);
    if (dup2(originalstdin, STDIN_FILENO) == -1)
        return (message_perror("Error restoring stdin"));
    return (0);
}
// child side of the process - make the execution
int child(t_minishell *mini)
{
    int i;
    i = -1;
    if (mini->s_cmd->prev->cmd != NULL)
        if (dup2(mini->s_cmd->prev->fd[0], STDIN_FILENO) == -1)
            return (close(mini->s_cmd->fd[0]), \
                close(mini->s_cmd->fd[1]), EXIT_FAILURE);
    if (mini->s_cmd->next->cmd != NULL && mini->s_cmd->next)
        if (dup2(mini->s_cmd->fd[1], STDOUT_FILENO) == -1)
            return (close(mini->s_cmd->fd[0]), \
                close(mini->s_cmd->fd[1]), EXIT_FAILURE);
    if (mini->s_cmd->prev->cmd != NULL)
        close(mini->s_cmd->prev->fd[0]);
    if (mini->s_cmd->next->cmd == NULL)
        close(mini->s_cmd->fd[0]);
    close(mini->s_cmd->fd[1]);
    if (mini->s_cmd->redir)
    {
        while (mini->s_cmd->redir[++i])
        {
            change_inf(mini->s_cmd->redir[i], mini->s_cmd->file[i]);
            change_out(mini->s_cmd->redir[i], mini->s_cmd->file[i]);
        }
    }
	printf("lol");
	printf("--%s--", mini->s_cmd->cmd);
    return (execute_cmd_buildin(mini));
}

int to_fork(t_minishell *mini, int *pids, int i, int n)
{
	pids[i] = fork();
	if (pids[i] < 0)
		return (free_scmd(mini->s_cmd), message_perror("Fork"));
	else if (pids[i] == 0)
	{
		child(mini);
		mini->s_cmd = mini->s_cmd->next;
	}
	else if (pids[i] > 0)
	{
		parent(mini->s_cmd);
		mini->s_cmd = mini->s_cmd->next;
		forker(n - 1, pids +1, mini);
	}
	return (0);
}

int	forker(int n, int *pids, t_minishell *mini)
{
	int	i;
	int originalstdout;

	i = 0;
	if (pipe(mini->s_cmd->fd) == -1)
		return (free_scmd(mini->s_cmd), message_perror("Pipe"));
	if (n > 0)
	{
		if(mini->s_cmd->cmd == NULL)
		{
			parent(mini->s_cmd);
			mini->s_cmd = mini->s_cmd->next;
			forker(n - 1, pids +1, mini);
		}
		else if(isbuildin(mini->s_cmd->cmd) == 0)
		{
			if(mini->s_cmd->next)
			{
				originalstdout = dup(STDOUT_FILENO);
				if (dup2(mini->s_cmd->prev->fd[1], STDOUT_FILENO) == -1)
					return(close(mini->s_cmd->fd[1]), close(mini->s_cmd->fd[0]), EXIT_FAILURE);
			}
			execute_buildin(mini);
			parent(mini->s_cmd);
			if(mini->s_cmd->next)
			{
				if (dup2(originalstdout, STDIN_FILENO) == -1)
					return (message_perror("Error restoring stdout"));
			}
			mini->s_cmd = mini->s_cmd->next;
			forker(n - 1, pids +1, mini);
		}
		else
			if(to_fork(mini, pids, i, n))
				return(1);
	}
	return (0);
}

void all_here_doc(t_minishell *mini, int n)
{
	int f;
	t_cmd	*cmd2;

	f = 0;
	cmd2 = mini->s_cmd;
	while(cmd2->cmd)
	{
		if(cmd2->file)
		{
			while(cmd2->file[f])
			{
				if(cmd2->redir[f] == '2')
					here_doc(cmd2->file[f]);
				f++;
			}
		}
		f = 0;
		cmd2 = cmd2->next;
	}
}

// the processus
int process(t_minishell *mini)
{
	pid_t	*pids;
	int		i;
	int		n;

	n = 0;
	i = 0;
	while(mini->s_cmd->cmd_arg[i])
		printf("->%s<-\n", mini->s_cmd->cmd_arg[i++]);
	i = 0;
	while (mini->cmd[n])
		n++;
	all_here_doc(mini, n);
	pids = ft_calloc(n, sizeof(pid_t));
	pids[i] = 1;
	while (mini->s_cmd->next)
		forker(n, pids, mini);
	i = 0;
	while (i < n)
	{		waitpid(pids[i], &mini->s_cmd->status, 0);
		if (WEXITSTATUS(mini->s_cmd->status) == 1)
			message_perror("WEXITSTATUS");
		i++;
	}
	return (0);
}
