#include "../include/minishell.h"

// main parsing func, block++ for amount of char* necessary to malloc.
static int	count_blocks(t_minishell *mini)
{
	int	i;

	i = 0;
	while (mini->arg[i])
	{
		if (mini->arg[i] == '\'' || mini->arg[i] == '\"')
		{
			if (!quote_check(mini, &i))
				return (1);
		}
		else if (mini->arg[i] == '|')
			mini->parse.block_count++;
		i++;
	}
	mini->parse.block_count++;
	return (0);
}

// mallocs char*s the necessary amount of char
static int	allocate_cmd(t_minishell *mini)
{
	int	i;

	i = 0;
	mini->cmd = ft_calloc((mini->parse.block_count + 1), sizeof(char *));
	if (!mini->cmd)
		return (malloc_error(mini, NULL), 1);
	while (mini->arg[i])
	{
		if (special_char_check(mini, &i))
			return (1);
		if (!mini->arg[i])
			break ;
		i++;
	}
	mini->cmd[mini->parse.c] = \
	ft_calloc((i + mini->parse.sub + 3), sizeof(char));
	if (!mini->cmd[mini->parse.c])
	{
		mini->cmd[mini->parse.c] = NULL;
		malloc_error(mini, mini->cmd);
		return (1);
	}
	mini->parse.end_block = i;
	if (get_block(mini))
		return (1);
	return (0);
}

static int	trim_cmd(t_minishell *mini)
{
	int		i;
	char	*temp;

	i = -1;
	while (mini->cmd[++i])
	{
		temp = mini->cmd[i];
		mini->cmd[i] = ft_strtrim(temp, " ");
		free(temp);
		temp = NULL;
		if (!mini->cmd[i])
		{
			mini->cmd[i]= NULL;
			return (malloc_error(mini, mini->cmd), 1);
		}
	}
	// if (count_2darray(mini->cmd) > 1)
	// {
	// 	i = 0;
	// 	while (mini->cmd[i]) // make sure this is handled properly depending on parsing
	// 	{
	// 		if (mini->cmd[i][0] == '\0')
	// 		{
	// 			parsing_error(mini);
	// 			return (1);
	// 		}
	// 		i++;
	// 	}
	// }
	return (0);
}

static int	parse(t_minishell *mini)
{
	char	*arg;

	arg = ft_strtrim(mini->arg, " \t\n");
	if (!arg)
		return (malloc_error(mini, NULL), 1);
	free(mini->arg);
	mini->arg = arg;
	if (count_blocks(mini))
		return (1);
	if (allocate_cmd(mini))
		return (1);
	if (trim_cmd(mini))
		return (1);
	if (redir_parsing(mini))
		return (1);
	return (0);
}

// reads user input w/ readline
void	read_input(t_minishell *mini)
{
	while (1)
	{
		mini->arg = readline("\033[92mminishell % \033[0m");
		if (mini->arg == NULL)
			break ;
		if (mini->arg[0] == '\0' || spacentabs_check(mini))
		{
			free(mini->arg);
			continue ;
		}
		add_history(mini->arg);
		if (parse(mini) == 0)
		{
			if (create_list(mini) == 0)
			{
				x_comm(mini);
			}
		}
	}
}
