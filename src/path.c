#include "../include/minishell.h"

// this function add / and command at the end of all possible path find in env
void	join_path_command(char **path, char *command)
{
	int	i_path;

	i_path = 0;
	while (path[i_path])
	{
		path[i_path] = ft_strjoin(path[i_path], "/");
		i_path++;
	}
	i_path = 0;
	while (path[i_path])
	{
		path[i_path] = ft_strjoin(path[i_path], command);
		i_path++;
	}
}

// this function check if one of the path is able to access the command
char	*test_path(char **path)
{
	int		i_path;
	char	*good_path;
	int		path_len;

	i_path = 0;
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

//This function first check if the path is absolute or relative. 
//Otherwise, it check if he can access the command whith env.
int	find_path(t_minishell *mini)
{
	int		len;
	char	**tab_path;
	
	if (access(mini->s_cmd->cmd, X_OK) == 0
		|| isbuildin(mini->s_cmd->cmd) == 0)
	{
		len = ft_strlen(mini->s_cmd->cmd);
		mini->s_cmd->path = ft_calloc((len + 1), sizeof(char));
		if (!mini->s_cmd->path)
			return (-1);
		ft_strlcpy(mini->s_cmd->path, mini->s_cmd->cmd, len + 1);
	}
	else
	{
		tab_path = ft_split(mini->path, ':');
		join_path_command(tab_path, mini->s_cmd->cmd);
		mini->s_cmd->path = test_path(tab_path);
		free_array(tab_path);
	}
	return (0);
}
