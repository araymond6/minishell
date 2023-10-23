#include "../include/minishell.h"

void	all_here_doc2(t_minishell *mini)
{
	int	i;

	i = 0;
	while (i < mini->token_count)
	{
		if (mini->token[i].type == HERE_DOC)
		{
			i++;
			here_doc(mini, mini->token[i].token);
		}
		i++;
	}
}

clear_s_cmd(t_cmd *cmd)
{
	if(cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
	if(cmd->cmd_arg)
	{
		free_array(cmd->cmd_arg);
		cmd->cmd_arg = NULL;
	}
	cmd->narg = 0;
}

void	join_path_command2(char **path, char *command)
{
	int		i_path;
	char	*path1;

	i_path = 0;
	if (!path)
	{
		message_perror("impossible to find PATH in the envp");
	}
		return ;
	while (path[i_path])
	{
		path1 = path[i_path];
		path[i_path] = ft_strjoin(path1, "/");
		free(path1);
		i_path++;
	}
	i_path = 0;
	while (path[i_path])
	{
		path1 = path[i_path];
		path[i_path] = ft_strjoin(path1, command);
		free(path1);
		i_path++;
	}
}

char	*test_path2(char **path)
{
	int		i_path;
	char	*good_path;
	int		path_len;

	i_path = 0;
	if (!path)
		return (NULL);
	while (path[i_path])
	{
		if (access(path[i_path], X_OK) == 0)
		{
			path_len = ft_strlen(path[i_path]) + 1;
			good_path = ft_calloc(path_len, sizeof(char));
			if (!good_path)
				return (NULL);
			ft_strlcpy(good_path, path[i_path], path_len);
			return (good_path);
		}
		i_path++;
	}
	return (NULL);
}

void	find_path2(t_minishell *mini)
{
	int		len;
	char	**tab_path;

	if (access(mini->s_cmd->cmd, X_OK) == 0)
	{
		len = ft_strlen(mini->s_cmd->cmd_arg[0]);
		mini->s_cmd->path = ft_calloc((len + 1), sizeof(char));
		if (!mini->s_cmd->path)
		{
			message_perror("Malloc error");
			return ;
		}
		ft_strlcpy(mini->s_cmd->path, mini->s_cmd->cmd, len + 1);
	}
	else
	{
		tab_path = ft_split(mini->path, ':');
		join_path_command2(tab_path, mini->s_cmd->cmd);
		mini->s_cmd->path = test_path2(tab_path);
		free_array(tab_path);
		tab_path = NULL;
	}
	return (0);
}

void child_redirection(t_minishell *mini, int n)
{
	if(n < mini->total_cmd)
	{
		if (dup2(mini->s_cmd->pipe[2 * (n - 1) + 1], STDOUT_FILENO) == -1)
			message_perror("Impossible to write in the pipe");
	}
	if(n != 1)
	{
		if (dup2(mini->s_cmd->pipe[2 * (n - 1)], STDIN_FILENO) == -1)
			message_perror("Impossible to read in the pipe");
	}
	manual_redirection(mini, n);
}

void child_path(t_minishell *mini)
{
	find_path2(mini);
	free(mini->s_cmd->cmd_arg[0]);
	mini->s_cmd->cmd_arg[0] = ft_calloc(ft_strlen(mini->s_cmd->path) + 1, sizeof(char));
	ft_strlcpy(mini->s_cmd->cmd_arg[0], mini->s_cmd->path, ft_strlen(mini->s_cmd->path) + 1);
}

char	*child_path_execve(char *string)
{
	char	*new_path_execve;
	int i;

	i = 0;
	new_path_execve = ft_calloc(ft_strlen(string) + 1, sizeof(char));
	while(string[i])
	{
		new_path_execve[i] = string[i];
		i++;
	}
	free(string);
	return(new_path_execve);
}

char	**child_array_execve(char **array)
{
	char	**new_array_execve;
	int i;
	int j;

	i = 0;
	while(array[i])
		i++;
	new_array_execve = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while(array[i])
	{
		new_array_execve[i] = ft_calloc(ft_strlen(array[i]) + 1, sizeof(char));
		while(array[i][j])
		{
			new_array_execve[i][j] = array[i][j];
			j++;
		}
		i++;
		j = 0;
	}
	free_array(array);
	return(new_array_execve);
}

void	child_closenfree(t_minishell *mini)
{
	int i;

	i = 1;
	if (mini->s_cmd->path)
		free(mini->s_cmd->path);
	if (mini->s_cmd->cmd_arg)
		free_array(mini->s_cmd->cmd_arg);
	while(i <= mini->total_cmd)
	{
		close(mini->s_cmd->pipe[2 * (i - 1)]);
		close(mini->s_cmd->pipe[2 * (i - 1) + 1]);
		i++;
	}
	if(mini->s_cmd->pipe)
		free(mini->s_cmd->pipe);
	if(mini->s_cmd->status)
		free(mini->s_cmd->status);
	close(mini->s_cmd->fd_stdin);
	close(mini->s_cmd->fd_stdout);
	if(mini->s_cmd->new_cmd)
		free(mini->s_cmd->new_cmd);
	if(mini->s_cmd->pids)
		free(mini->s_cmd->pids);
}

void execve_failed(char *path_execve, char **array_execve)
{
	free(path_execve);
	free_array(array_execve);
	message_perror("Impossible to execute the command");
}

void	child2(t_minishell *mini, int n)
{
	char	*path_execve;
	char	**array_execve;

	mini->sigact.sa_handler = sigint_handler;
	signal(SIGQUIT, SIG_DFL);
	sigaction(SIGINT, &mini->sigact, NULL);
	mini->sigact.sa_handler = signal_handler;
	child_path(mini);
	child_redirection(mini, n);
	path_execve = child_path_execve(mini->s_cmd->path);
	array_execve = child_array_execve(mini->s_cmd->cmd_arg); //////s'il y a un probleme de leaks on peut changer ca pour enregistrer seulement l'adresse au lieu de recopier en mallocant
	child_closenfree(mini);
	if (execve(path_execve, array_execve, mini->envp) == -1)
		execve_failed(path_execve, array_execve);
}

int	parent2(t_minishell *mini, int n)
{
	if(n != 1)
	{
		if (dup2(mini->s_cmd->pipe[2 * (n - 1)], STDIN_FILENO) == -1)
			message_perror("Impossible to read in the pipe");
	}
	return (0);
}

void exec_bash_cmd(t_minishell *mini, int n)
{
	// le path n<est pas encore set//
	
	set_signal_for_process(mini);
	mini->s_cmd->pids[n - 1] = fork();
	if (mini->s_cmd->pids[n - 1] < 0)
	{
		message_perror("Crash in the fork function");
		clear_s_cmd(mini->s_cmd);
	}
	else if (mini->s_cmd->pids[n - 1] == 0)
		child2(mini, n);
	else if (mini->s_cmd->pids[n - 1] > 0)
		parent2(mini, n);
	return (0);
}

int	forker2(t_minishell *mini)
{
	int	r;
	int n;

	r = 0;
	n = 1;
	while(n <= mini->total_cmd)
	{
		find_cmd(mini, n);
		if (mini->s_cmd->cmd_arg == NULL)
			null_command2(mini, n);
		else if (mini->s_cmd->cmd_arg[0] == "")
			null_command2(mini, n);
		else if (isbuildin(mini->s_cmd->cmd_arg[0]) == 0)
			exec_buildin2(mini, n);
		else
			exec_bash_cmd(mini, n);
		n++;
	}
	return (0);
}

int	time_to_execute(t_minishell *mini)
{
	int		i;
	int		total_cmd;

	i = 0;
	mini->s_cmd = ft_calloc(1, sizeof(t_cmd));
	initialize_scmd(mini);
	all_here_doc2(mini);
	forker2(mini);
	while (i < mini->total_cmd)
	{
		waitpid(mini->s_cmd->pids[i], &mini->s_cmd->status[i], 0);
		i++;
	}
	free_scmd(mini->s_cmd);
}
