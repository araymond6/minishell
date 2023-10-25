#include "../include/minishell.h"

static int	checks_after2(t_minishell *mini, int *i)
{
	if (*i == mini->token_count)
		return (parsing_error(mini), 1);
	else
	{
		if(mini->token[*i].type == WHITESPACE)
		{
			i++;
			if(*i == mini->token_count)
				return (parsing_error(mini), 1);
		}
		if (mini->token[*i].type == STRING
			|| mini->token[*i].type == DOLLAR_SIGN
			|| mini->token[*i].type == SINGLE_QUOTE
			|| mini->token[*i].type == DOUBLE_QUOTE)
			return(0);
		else if(mini->token[*i].type == REDIRECT_INPUT
			|| mini->token[*i].type == REDIRECT_OUTPUT
			|| mini->token[*i].type == HERE_DOC
			|| mini->token[*i].type == APPEND
			|| mini->token[*i].type == PIPE)
			return (parsing_error(mini), 1);
	}	
}

static int	checks_after_pipe(t_minishell *mini, int *i)
{
	if (*i == mini->token_count)
		return (parsing_error(mini), 1);
	else
	{
		if(mini->token[*i].type == WHITESPACE)
		{
			i++;
			if(*i == mini->token_count)
				return (parsing_error(mini), 1);
		}
		if(mini->token[*i].type == PIPE)
			return (parsing_error(mini), 1);
	}	
}

static int	checks_before2(t_minishell *mini, int *i)
{
	i--;
	if(i == 0)
		return (parsing_error(mini), 1);
	i--;
	if(mini->token[*i].type == WHITESPACE)
	{
		i--;
		if(*i == 0)
			return (parsing_error(mini), 1);
	}
	if (mini->token[*i].type == STRING
		|| mini->token[*i].type == DOLLAR_SIGN
		|| mini->token[*i].type == SINGLE_QUOTE
		|| mini->token[*i].type == DOUBLE_QUOTE)
		return(0);
	else if(mini->token[*i].type == REDIRECT_INPUT
		|| mini->token[*i].type == REDIRECT_OUTPUT
		|| mini->token[*i].type == HERE_DOC
		|| mini->token[*i].type == APPEND
		|| mini->token[*i].type == PIPE)
		return (parsing_error(mini), 1);
}

int	redir_parsing2(t_minishell *mini)
{
	int	i;

	i = 0;
	while(i < mini->token_count)
	{
		if(mini->token[i].type == REDIRECT_INPUT
			|| mini->token[i].type == REDIRECT_OUTPUT
				|| mini->token[i].type == HERE_DOC
				|| mini->token[i].type == APPEND)
		{
			i++;
			if (checks_after2(mini, &i) == 1)
				return (1);
		}
	}
	return (0);
}

int	pipe_parsing2(t_minishell *mini)
{
	int	i;

	i = 0;
	while(i < mini->token_count)
	{
		if(mini->token[i].type == PIPE)
		{
			i++;
			if (checks_after_pipe(mini, &i) == 1)
				return (1);
			if (checks_before2(mini, &i))
				return (1);
		}
	}
	return (0);
}