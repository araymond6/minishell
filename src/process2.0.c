#include "../include/minishell.h"

/*
int	nb_cmd(t_minishell *mini)
{
	int i;
	int nb_c;

	nb_c = 1;
	i = 0;
	while (i < mini->token_count)
	{
		if (mini->token[i].type == PIPE
			&& mini->token->indoublequote == 0
			&& mini->token->inquote == 0)
			nb_c++;
		i++;
	}
	return (nb_c);
}
*/

int len_file(t_minishell *mini, int i)
{
	int len;

	while( mini->token[i].indoublequote == 0 && mini->token[i].inquote == 0)
	{
		len += mini->token[i].len;
		i++;
	}
	return(len);
}

int nb_redir(t_minishell *mini, int i)
{
	int nb_redir;

	nb_redir = 0;
	while (i < mini->token_count)
	{
		if(	mini->token[i].type == PIPE && mini->token->indoublequote == 0
			&& mini->token->inquote == 0)
			break;
		if((mini->token[i].type == HERE_DOC || mini->token[i].type == APPEND
			|| mini->token[i].type == REDIRECT_INPUT
			|| mini->token[i].type == REDIRECT_OUTPUT)
			&& mini->token[i].inquote == 0
			&& mini->token[i].indoublequote == 0)
			nb_redir++;
		i++;
	}
	return(i);
}

char *file_name(t_minishell *mini, int i)
{
	int f;
	int l;
	char *file;

	f = 0;
	l = 0;
	file = ft_calloc(len_file(mini, i) + 1, sizeof(char));
	while (mini->token[i].type != WHITESPACE
		&& mini->token[i].indoublequote == 0
		&& mini->token[i].inquote == 0
		&& i < mini->token_count)
	{
		while (l < mini->token[i].len)
		{
			file[f] = mini->token[i].token[l];
			f++;
			l++;
		}
		l = 0;
		i++;
	}
	return (file);
}

void	all_here_doc2(t_minishell *mini)
{
	int	i;
	char *file;

	i = 0;
	while (i < mini->token_count)
	{
		if (mini->token[i].type == HERE_DOC
			&& mini->token->indoublequote == 0
			&& mini->token->inquote == 0)
		{
			file = file_name(mini, i + 1);
			here_doc(mini, file);
		}
		i++;
	}
}

void	find_redirection(t_minishell *mini, int i)
{
	int r;

	r = 0;
	mini->s_cmd->nredir = nb_redir(mini, i);
	mini->s_cmd->redir = ft_calloc(mini->s_cmd->nredir, sizeof(int));
	while (i < mini->token_count)
	{
		if(	mini->token[i].type == PIPE && mini->token->indoublequote == 0
			&& mini->token->inquote == 0)
			break;
		if((mini->token[i].type == HERE_DOC || mini->token[i].type == APPEND
			|| mini->token[i].type == REDIRECT_INPUT
			|| mini->token[i].type == REDIRECT_OUTPUT)
			&& mini->token[i].inquote == 0
			&& mini->token[i].indoublequote == 0)
		{
			mini->s_cmd->redir[r] = i;
			r++;
		}
	}
}

int nb_carg(t_minishell *mini, int i)
{
	int r;

	r = 0;
	while (i < mini->token_count)
	{
		if(	mini->token[i].type == PIPE && mini->token->indoublequote == 0
			&& mini->token->inquote == 0)
			break;
		if((mini->token[i].type == HERE_DOC || mini->token[i].type == APPEND
			|| mini->token[i].type == REDIRECT_INPUT
			|| mini->token[i].type == REDIRECT_OUTPUT)
			&& mini->token[i].inquote == 0
			&& mini->token[i].indoublequote == 0)
		{
			mini->s_cmd->redir[r] = i;
			r++;
		}
	}
}

void	find_cmd(t_minishell *mini, int i)
{
	int r;
	int nb_cargs;

	r = 0;
	nb_cargs = nb_carg(mini, i);
	mini->s_cmd->redir = ft_calloc(mini->s_cmd->nredir, sizeof(int));
	while (i < mini->token_count)
	{
		if(	mini->token[i].type == PIPE && mini->token->indoublequote == 0
			&& mini->token->inquote == 0)
			break;
		if((mini->token[i].type == HERE_DOC || mini->token[i].type == APPEND
			|| mini->token[i].type == REDIRECT_INPUT
			|| mini->token[i].type == REDIRECT_OUTPUT)
			&& mini->token[i].inquote == 0
			&& mini->token[i].indoublequote == 0)
		{
			mini->s_cmd->redir[r] = i;
			r++;
		}
	}
}

int find_token(t_minishell *mini, int i)
{
	find_redirection(mini, i);
	find_cmd(mini, i);
	return(i);
}

int	forker2(t_minishell *mini)
{
	int n;
	int	r;

	n = 0;
	r = 0;
	while(n < mini->nb_c)
	{
		find_token(mini);

	}
	if (n > 0)
	{
		if (mini->s_cmd->cmd == NULL)
		{
			if (null_command(mini, pids, n) == 1)
				return (free(pids), 1);
		}
		else if (isbuildin(mini->s_cmd->cmd) == 0 && n > 1)
		{
			if (exec_buildin(mini, pids, n) == 1)
				return (free(pids), 1);
		}
		else if (isbuildin(mini->s_cmd->cmd) == 0 && n == 1)
		{
			if (last_buildin(mini) == 1)
				return (free(pids), 1);
		}
		else
		{
			if (to_fork(mini, pids, n))
				return (free(pids), 1);
		}
	}
	return (0);
}

int	time_to_execute(t_minishell *mini)
{
	int		nb_c;

	mini->s_cmd = ft_calloc(1, sizeof(t_cmd));
	initialize_scmd(mini);
	all_here_doc2(mini);
	forker2(mini);
}

/*

pids = ft_calloc(n, sizeof(pid_t));
	pids[0] = 1;
	forker(n, pids, mini);
	mini->s_cmd->c = 0;
	while (mini->s_cmd->c < n)
	{
		waitpid(pids[mini->s_cmd->c], &mini->s_cmd->status, 0);
		mini->s_cmd->c++;
	}
	free(pids);
	return (0);

*/