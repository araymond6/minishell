#include "../include/minishell.h"

void	parse_exit(t_minishell *mini)
{
	perror("Error");
	exit_program(mini);
}

void	parsing_error(t_minishell *mini)
{
	int	i;

	mini->exit_code = 2;
	i = 0;
	if (mini->cmd)
	{
		while (mini->cmd[i])
		{
			free(mini->cmd[i]);
			mini->cmd[i] = NULL;
			i++;
		}
		free(mini->cmd);
		mini->cmd = NULL;
	}
	clear_mini(mini);
	if (write(STDOUT_FILENO, "parse error\n", 12) == -1)
		parse_exit(mini);
}

static char	*while_env(t_minishell *mini, char *new)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (mini->envp[i])
	{
		if (ft_strncmp(mini->envp[i], new, ft_strlen(new)) == 0)
		{
			free(new);
			new = ft_calloc((ft_strlen(mini->envp[i]) + 1), sizeof(char));
			if (!new)
				return (NULL);
			while (mini->envp[i][k])
			{
				new[k] = mini->envp[i][k];
				k++;
			}
			return (new);
		}
		(i)++;
	}
	return (NULL);
}

// checks our minishell's envp for the env variable, returns char* if found;
char	*check_env(t_minishell *mini, char *arg)
{
	char	*new;

	if (!arg || arg[0] == '\0')
		return (NULL);
	new = ft_strjoin(arg, "=");
	if (!new)
	{
		free(arg);
		return (malloc_error(mini, NULL), NULL);
	}
	new = while_env(mini, new);
	if (!new)
		return (ft_strdup(""));
	return (new);
}