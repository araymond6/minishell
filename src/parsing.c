#include "../include/minishell.h"

static int	check_pipe(char *arg, int *i, int *temp, t_type type)
{
	while (*temp >= 0)
	{
		type = get_type(&arg[*temp]);
		if (type != WHITESPACE && type != PIPE) 
			break ;
		else if (type == PIPE)
			return (1);
		else
			(*temp)--;
	}
	if (!arg[*i + 1] || arg[0] == '|' || *temp == -1)
		return (1);
	*temp = *i + 1;
	while (arg[*temp])
	{
		type = get_type(&arg[*temp]);
		if (type != WHITESPACE && type != PIPE)
			break ;
		else if (type == PIPE)
			return (1);
		else 
			(*temp)++;
		if (arg[*temp] == 0)
			return (1);
	}
	return (0);
}

int	pipe_parsing(t_minishell *mini, char *arg)
{
	int		i;
	int		temp;
	t_type	type;

	i = 0;
	type = 0;
	while (arg[i])
	{
		if (arg[i] == '|')
		{
			temp = i - 1;
			if (check_pipe(arg, &i, &temp, type) == 1)
				return (parsing_error(mini), 1);
		}
		i++;
	}
	return (0);
}

void	read_input(t_minishell *mini)
{
	while (1)
	{
		signal_reset(mini);
		mini->arg = readline("\033[92mminishell % \033[0m");
		if (mini->arg == NULL)
			break ;
		add_history(mini->arg);
		if (mini->arg[0] == '\0' || whitespace_check(mini->arg) == 1 || pipe_parsing(mini, mini->arg) == 1)
		{
			free(mini->arg);
			continue ;
		}
		mini->token = tokenize(mini, mini->arg);
		if (!mini->token)
		{
			clear_mini(mini);
			continue ;
		}
		count_heredoc(mini);
		set_heredoc_flag(mini);
		print_tokens(mini->token, mini->token_count);
		if (mini->token)
			time_to_execute(mini);
		clear_mini(mini);
	}
}