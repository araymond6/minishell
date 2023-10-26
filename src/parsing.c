#include "../include/minishell.h"

int	pipe_parsing(t_minishell *mini, char *arg) //TODO: Shorten this
{
	int		i;
	int		temp;
	t_type	type;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '|')
		{
			temp = i - 1;
			while (temp >= 0)
			{
				type = get_type(&arg[temp]);
				if (type != WHITESPACE && type != PIPE) 
					break ;
				else if (type == PIPE)
					return (parsing_error(mini), 1);
				else
					temp--;
			}
			if (!arg[i + 1] || arg[0] == '|')
				return (parsing_error(mini), 1);
			temp = i + 1;
			while (arg[temp])
			{
				type = get_type(&arg[temp]);
				if (type != WHITESPACE && type != PIPE)
					break ;
				else if (type == PIPE)
					return (parsing_error(mini), 1);
				else 
					temp++;
			}
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
		count_heredoc(mini);
		set_heredoc_flag(mini); //TODO: place after redir parse
		if (mini->token)
		{
			// if (create_list(mini) == 0)
			// 	x_comm(mini);
		}
		clear_mini(mini);
	}
}