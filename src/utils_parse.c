#include "../include/minishell.h"

char	*get_path(t_minishell *mini)
{
	int		i;
	char	*path;

	i = -1;
	path = "PATH=";
	while (mini->envp[++i])
	{
		if (!ft_strncmp(path, mini->envp[i], ft_strlen(path)))
		{
			return (mini->envp[i]);
		}
	}
	return (NULL);
}

// zeroes t_minishell and set envp and signal handlers
void	initialize_mini(t_minishell *mini, char **envp)
{
	ft_bzero(mini, sizeof(t_minishell));
	mini->envp = envp;
	mini->path = get_path(mini);
	signal_reset(mini);
}

void	clear_mini(t_minishell *mini)
{
	int	i;

	i = 0;
	ft_bzero(&mini->parse, sizeof(t_parse));
	if (mini->arg)
	{
		free(mini->arg);
		mini->arg = NULL;
	}
	if (mini->cmd != NULL)
		free_array(mini->cmd);
	if (mini->token)
	{
		while (i < mini->token_count)
			free(mini->token[i++].token);
		free(mini->token);
	}
	mini->cmd = NULL;
}

// sets error code to 1, prints error message 
// and frees array if deemed necessary
void	malloc_error(t_minishell *mini, char **to_free)
{
	mini->exit_code = 1;
	if (to_free)
	{
		free_array(to_free);
		to_free = NULL;
	}
	printf("malloc error\n");
}
