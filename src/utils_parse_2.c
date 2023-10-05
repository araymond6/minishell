#include "../include/minishell.h"

void	parse_exit(t_minishell *mini)
{
	perror("Error");
	exit_program(mini);
}

void	parsing_error(t_minishell *mini)
{
	mini->parse.block_count = 0;
	mini->exit_code = 2;
	if (write(STDOUT_FILENO, "parse error\n", 12) == -1)
		parse_exit(mini);
}

static char	*while_env(t_minishell *mini, int *i, int *k, char *new)
{
	while (mini->envp[*i])
	{
		if (ft_strncmp(mini->envp[*i], new, ft_strlen(new)) == 0)
		{
			free(new);
			new = ft_calloc((ft_strlen(mini->envp[*i]) + 1), sizeof(char));
			if (!new)
				return (NULL);
			while (mini->envp[*i][*k])
			{
				new[*k] = mini->envp[*i][*k];
				(*k)++;
			}
			return (new);
		}
		(*i)++;
	}
	return (NULL);
}

// checks our minishell's envp for the env variable, returns char *;
char	*check_env(t_minishell *mini, char *arg)
{
	int		i;
	int		k;
	char	*new;

	i = 0;
	k = 0;
	if (!arg || arg[0] == '\0')
		return (NULL);
	new = ft_strjoin(arg, "=");
	if (!new)
	{
		free(arg);
		malloc_error(mini);
	}
	new = while_env(mini, &i, &k, new);
	if (!new || new[0] == '\0')
		return (NULL);
	return (new);
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
