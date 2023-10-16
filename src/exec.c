#include "../include/minishell.h"

char	*create_cmd(t_minishell *mini, char *cmd)
{
	cmd = ft_calloc(ft_strlen(mini->s_cmd->path) + 1, sizeof(char));
	if (cmd == NULL)
		return (free_scmd(mini->s_cmd), NULL);
	ft_strlcpy(cmd, mini->s_cmd->path, ft_strlen(mini->s_cmd->path));
	return (cmd);
}

char	**create_tab_path(t_minishell *mini, char **tab_path)
{
	int	len;

	len = 0;
	while (mini->s_cmd->cmd_arg[len])
		len++;
	tab_path = ft_calloc(len + 1, sizeof(char *));
	if (tab_path == NULL)
		return (NULL);
	len = 0;
	while (mini->s_cmd->cmd_arg[len])
	{
		tab_path[len] = ft_calloc(ft_strlen(mini->s_cmd->cmd_arg[len]), sizeof(char));
		if (tab_path == NULL)
			return (NULL);
		ft_strlcpy(tab_path[len], mini->s_cmd->cmd_arg[len], ft_strlen(mini->s_cmd->path));
		len++;
	}
	return (tab_path);
}

// check if it<s a buildin or not and execute it
int	execute_cmd(t_minishell *mini)
{
	char	*cmd;
	char	**tab_path;
	int		len;

	len = 0;
	if (ft_strlen(mini->s_cmd->cmd) == 0)
		exit(0);
	else if (isbuildin(mini->s_cmd->cmd) == 0)
		exit(execute_buildin(mini));
	else
	{
		cmd = NULL;
		tab_path = NULL;
		signal(SIGQUIT, SIG_DFL);
		cmd = ft_calloc(ft_strlen(mini->s_cmd->path) + 1, sizeof(char));
		if (cmd == NULL)
			return (free_scmd(mini->s_cmd), 1);
		ft_strlcpy(cmd, mini->s_cmd->path, ft_strlen(mini->s_cmd->path) + 1);
		while (mini->s_cmd->cmd_arg[len])
			len++;
		tab_path = ft_calloc(len + 1, sizeof(char*));
		if (tab_path == NULL)
			return (free(cmd), free_scmd(mini->s_cmd), 1);
		len = 0;
		while (mini->s_cmd->cmd_arg[len])
		{
			tab_path[len] = ft_calloc(ft_strlen(mini->s_cmd->cmd_arg[len]) + 1, sizeof(char));
			if (tab_path == NULL)
			{
				free(cmd);
				free_array(tab_path);
				free_scmd(mini->s_cmd);
				return (1);
			}
			ft_strlcpy(tab_path[len], mini->s_cmd->cmd_arg[len], ft_strlen(mini->s_cmd->cmd_arg[len] + 1));
			len++;
		}
		free_scmd(mini->s_cmd);
		if (execve(cmd, tab_path, mini->envp) == -1)
		{
			free(cmd);
			free_array(tab_path);
			exit(message_perror("EXECVE"));
		}
	}
	return (0);
}


// the processus
int	process(t_minishell *mini)
{
	pid_t	*pids;
	int		i;
	int		n;

	n = 0;
	i = 0;
	while (mini->cmd[n])
		n++;
	all_here_doc(mini);
	pids = ft_calloc(n, sizeof(pid_t));
	pids[i] = 1;
	forker(n, pids, mini);
	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &mini->s_cmd->status, 0);
		i++;
	}
	free(pids);
	return (0);
}
