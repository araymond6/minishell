#include "../include/minishell.h"

void	child_path(t_minishell *mini)
{
	find_path2(mini);
	free(mini->s_cmd->cmd_arg[0]);
	mini->s_cmd->cmd_arg[0] = NULL;
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
	return(new_path_execve);
}

char	**child_array_execve(char **array)
{
	char	**new_array_execve;
	int i;
	int j;

	i = 0;
	j = 0;
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
	array = NULL;
	return(new_array_execve);
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
	manual_redirection(mini, n);
	path_execve = child_path_execve(mini->s_cmd->path);
	array_execve = child_array_execve(mini->s_cmd->cmd_arg);
	mini->s_cmd->cmd_arg = NULL;
	child_closenfree(mini);
	execve(path_execve, array_execve, mini->envp);
	execve_failed(path_execve, array_execve);
}