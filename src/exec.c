#include "../include/minishell.h"

char	*create_cmd(t_minishell *mini)
{
	char	*cmd;

	cmd = ft_calloc(ft_strlen(mini->s_cmd->path) + 1, sizeof(char));
	if (cmd == NULL)
		return (free_scmd(mini->s_cmd), NULL);
	ft_strlcpy(cmd, mini->s_cmd->path, ft_strlen(mini->s_cmd->path));
	return (cmd);
}

char	**create_tab_path(t_minishell *mini, char **tab_path)
{
	mini->s_cmd->c = 0;
	while (mini->s_cmd->cmd_arg[mini->s_cmd->c])
		mini->s_cmd->c++;
	tab_path = ft_calloc(mini->s_cmd->c + 1, sizeof(char *));
	if (tab_path == NULL)
		return (NULL);
	mini->s_cmd->c = 0;
	while (mini->s_cmd->cmd_arg[mini->s_cmd->c])
	{
		tab_path[mini->s_cmd->c] = \
			ft_calloc(ft_strlen(mini->s_cmd->cmd_arg[mini->s_cmd->c]), \
			sizeof(char));
		if (tab_path == NULL)
			return (NULL);
		ft_strlcpy(tab_path[mini->s_cmd->c], \
			mini->s_cmd->cmd_arg[mini->s_cmd->c], ft_strlen(mini->s_cmd->path));
		mini->s_cmd->c++;
	}
	return (tab_path);
}

char	**create_tab(t_minishell *mini, char *cmd)
{
	char	**tab_path;
	int		len;

	mini->s_cmd->c = 0;
	while (mini->s_cmd->cmd_arg[mini->s_cmd->c])
		mini->s_cmd->c++;
	tab_path = ft_calloc(mini->s_cmd->c + 1, sizeof(char *));
	if (tab_path == NULL)
		return (free(cmd), free_scmd(mini->s_cmd), NULL);
	mini->s_cmd->c = 0;
	while (mini->s_cmd->cmd_arg[mini->s_cmd->c])
	{
		len = ft_strlen(mini->s_cmd->cmd_arg[mini->s_cmd->c]);
		tab_path[mini->s_cmd->c] = \
			ft_calloc(len + 1, sizeof(char));
		if (tab_path == NULL)
		{
			free(cmd);
			free_array(tab_path);
			free_scmd(mini->s_cmd);
			return (NULL);
		}
	}
	return (tab_path);
}

void	free_execve(char *cmd, char **tab_path)
{
	if (cmd)
		free(cmd);
	if (tab_path)
		free_array(tab_path);
	exit(message_perror("EXECVE"));
}

// check if it<s a buildin or not and execute it
int	execute_cmd(t_minishell *mini)
{
	char	*cmd;
	char	**tab_path;

	mini->s_cmd->c = 0;
	if (ft_strlen(mini->s_cmd->cmd) == 0)
		exit(0);
	else if (isbuildin(mini->s_cmd->cmd) == 0)
		exit(execute_buildin(mini));
	else
	{
		signal(SIGQUIT, SIG_DFL);
		cmd = ft_calloc(ft_strlen(mini->s_cmd->path) + 1, sizeof(char));
		if (cmd == NULL)
			return (free_scmd(mini->s_cmd), 1);
		ft_strlcpy(cmd, mini->s_cmd->path, ft_strlen(mini->s_cmd->path));
		mini->s_cmd->c = 0;
	while (mini->s_cmd->cmd_arg[mini->s_cmd->c])
		mini->s_cmd->c++;
	tab_path = ft_calloc(mini->s_cmd->c + 1, sizeof(char *));
	if (tab_path == NULL)
		return (1);
	mini->s_cmd->c = 0;
	while (mini->s_cmd->cmd_arg[mini->s_cmd->c])
	{
		tab_path[mini->s_cmd->c] = \
			ft_calloc(ft_strlen(mini->s_cmd->cmd_arg[mini->s_cmd->c]), \
			sizeof(char));
		if (tab_path == NULL)
			return (1);
		ft_strlcpy(tab_path[mini->s_cmd->c], \
			mini->s_cmd->cmd_arg[mini->s_cmd->c], ft_strlen(mini->s_cmd->path));
		mini->s_cmd->c++;
	}
		if (tab_path == NULL)
			return (1);
		free_scmd(mini->s_cmd);
		if (execve(cmd, tab_path, mini->envp) == -1)
			free_execve(cmd, tab_path);
	}
	return (0);
}


// the processus
int	process(t_minishell *mini)
{
	pid_t	*pids;
	int		n;

	n = 0;
	while (mini->cmd[n])
		n++;
	all_here_doc(mini);
	pids = ft_calloc(n, sizeof(pid_t));
	pids[0] = 1;
	forker(n, pids, mini);
	mini->s_cmd->c = 0;
	while (mini->s_cmd->c < n)
	{
		waitpid(pids[mini->s_cmd->c], &mini->s_cmd->status, 0);
		mini->s_cmd->c++;
	}
	free(pids);
	return (0);
}
