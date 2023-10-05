#include "../include/minishell.h"

//TODO: FIX PARSE_ERROR

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
				return (0);
		}
		else if (mini->arg[i] == '|')
			mini->parse.block_count++;
		i++;
	}
	mini->parse.block_count++;
	return (1);
}

// mallocs char*s the necessary amount of char
static void	allocate_cmd(t_minishell *mini)
{
	int	i;

	i = 0;
	mini->cmd = ft_calloc((mini->parse.block_count + 1), sizeof(char *));
	if (!mini->cmd)
		malloc_error(mini);
	while (mini->arg[i])
	{
		special_char_check(mini, &i);
		if (!mini->arg[i])
			break ;
		i++;
	}
	mini->cmd[mini->parse.c] = \
	ft_calloc((i + mini->parse.sub + 3), sizeof(char));
	if (!mini->cmd[mini->parse.c])
		malloc_error(mini);
	mini->parse.end_block = i;
	get_block(mini);
}

static int	trim_cmd(t_minishell *mini)
{
	int		i;
	char	*temp;

	i = -1;
	while (mini->cmd[++i])
	{
		temp = mini->cmd[i];
		mini->cmd[i] = ft_strtrim(mini->cmd[i], " ");
		if (!mini->cmd[i])
			malloc_error(mini);
		free(temp);
		temp = NULL;
	}
	i = 0;
	while (mini->cmd[i])
	{
		if (mini->cmd[i][0] == '\0')
		{
			printf("cmd %d: %s", i, mini->cmd[i]); // THERE IS A PRINTF HERE
			parsing_error(mini);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	parse(t_minishell *mini)
{
	char	*arg;

	arg = ft_strtrim(mini->arg, " ");
	free(mini->arg);
	if (!arg)
		malloc_error(mini);
	mini->arg = arg;
	if (!count_blocks(mini))
		return (1);
	allocate_cmd(mini);
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
			if(quote_n_create(mini) == 0)
			{
				x_comm(mini);
			}
		}
		clear_mini(mini);
	}
}
