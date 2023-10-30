#include "../include/minishell.h"

void	nb_of_arg_lopp(int i, int n, t_minishell *mini)
{
	while (i < mini->token_count && mini->token[i].cmd_n == n)
	{
		if (mini->token[i].type == HERE_DOC
			|| mini->token[i].type == APPEND
			|| mini->token[i].type == REDIRECT_INPUT
			|| mini->token[i].type == REDIRECT_OUTPUT)
			i += 2;
		else
		{
			while (i < mini->token_count
				&& mini->token[i].cmd_n == n
				&& mini->token[i].type == STRING)
			{
				i++;
				mini->s_cmd->narg++;
			}
			return ;
		}
	}
}

void	nb_of_arg(t_minishell *mini, int n)
{
	int	i;

	i = 0;
	mini->s_cmd->narg = 0;
	while (i < mini->token_count && mini->token[i].cmd_n != n)
		i++;
	nb_of_arg_lopp(i, n, mini);
}

void	cpy_cmd(t_minishell *mini, int n, int i)
{
	int	r;

	r = 0;
	while (i < mini->token_count
		&& mini->token[i].cmd_n == n
		&& mini->token[i].type == STRING)
	{
		mini->s_cmd->cmd_arg[r] = \
			ft_calloc(ft_strlen(mini->token[i].token) + 1, sizeof(char));
		ft_strlcpy(mini->s_cmd->cmd_arg[r], mini->token[i].token,
			ft_strlen(mini->token[i].token) + 1);
		i++;
		r++;
	}
}

void	find_cmd(t_minishell *mini, int n)
{
	int	i;

	i = 0;
	nb_of_arg(mini, n);
	mini->s_cmd->cmd_arg = ft_calloc(mini->s_cmd->narg + 1, sizeof(char *));
	if(!mini->s_cmd->cmd_arg)
		return;
	while (i < mini->token_count && mini->token[i].cmd_n != n)
		i++;
	while (i < mini->token_count && mini->token[i].cmd_n == n)
	{
		if (mini->token[i].type == HERE_DOC
			|| mini->token[i].type == APPEND
			|| mini->token[i].type == REDIRECT_INPUT
			|| mini->token[i].type == REDIRECT_OUTPUT)
			i += 2;
		else
			return (cpy_cmd(mini, n, i));
	}
}
