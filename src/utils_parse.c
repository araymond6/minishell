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
	mini->sigact.sa_handler = signal_handler;
	sigaction(SIGINT, &mini->sigact, NULL);
	sigaction(SIGQUIT, &mini->sigact, NULL);
}

void	clear_mini(t_minishell *mini)
{
	int	i;

	i = 0;
	mini->parse.block_count = 0;
	mini->parse.c = 0;
	mini->parse.end_block = 0;
	mini->parse.start_block = 0;
	mini->parse.sub = 0; //TODO: free shit (envp and more)
	if (mini->arg)
	{
		free(mini->arg);
		mini->arg = NULL;
	}
	if (mini->cmd)
		free_array(mini->cmd);
}

// sets error code to 1, prints error message 
// and frees array if deemed necessary
void	malloc_error(t_minishell *mini, char **to_free)
{
	mini->exit_code = 1;
	if (to_free)
		free_array(to_free);
	printf("malloc error\n");
}
