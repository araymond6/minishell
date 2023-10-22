#include "../include/minishell.h"

void	all_here_doc2(t_minishell *mini)
{
	int	i;

	i = 0;
	while (i < mini->token_count)
	{
		if (mini->token[i].type == HERE_DOC)
		{
			i++;
			here_doc(mini, mini->token[i].token);
		}
		i++;
	}
}

void	nb_carg(t_minishell *mini, int n)
{
	int i = 0;

	mini->s_cmd->narg == 0;
	while (i < mini->token_count && mini->token[i].no_cmd != n)
		i++;
	while (i < mini->token_count && mini->token[i].no_cmd == n)
	{
		if(mini->token[i].type == HERE_DOC
			|| mini->token[i].type == APPEND
			|| mini->token[i].type == REDIRECT_INPUT
			||  mini->token[i].type == REDIRECT_OUTPUT)
			i += 2;
		else
		{
			while (i < mini->token_count
				&& mini->token[i].no_cmd == n
				&& mini->token[i].type == STRING)
			{
				i++;
				mini->s_cmd->narg++;
			}
			return;
		}
		i++;
	}
}

void cpy_cmd(t_minishell *mini, int n, int i)
{
	int r;

	r = 0;
	
	while (i < mini->token_count
		&& mini->token[i].no_cmd == n
		&& mini->token[i].type == STRING)
	{
		mini->s_cmd->cmd_arg[r] = ft_calloc(mini->token[i].len + 1, sizeof(char));
		ft_strlcpy(mini->s_cmd->cmd_arg[r], mini->token[i].token, mini->token[i].len + 1);
		i++;
		r++;
	}
}

void	find_cmd(t_minishell *mini, int n)
{
	int i;

	i = 0;
	nb_carg(mini, n);
	mini->s_cmd->cmd_arg = ft_calloc(mini->s_cmd->narg, sizeof(char*));
	while (i < mini->token_count && mini->token[i].no_cmd != n)
		i++;
	while (i < mini->token_count && mini->token[i].no_cmd == n)
	{
		if(mini->token[i].type == HERE_DOC
			|| mini->token[i].type == APPEND
			|| mini->token[i].type == REDIRECT_INPUT
			||  mini->token[i].type == REDIRECT_OUTPUT)
			i += 2;
		else
			return(cpy_cmd(mini, n, i));
		i++;
	}
}

int	forker2(t_minishell *mini)
{
	int	r;
	int n;

	r = 0;
	n = 0;
	while(n < mini->total_cmd)
	{
		find_cmd(mini, n);
		if (mini->s_cmd->cmd_arg == NULL)
		{
			//changer les redirections puis les remettre dans les bonne places;
			//puis faire un clear de la struct pour remettre a zero ce qui doit e[tre remis a zero]
			if (mini->s_cmd->redir)
			{
				while (mini->s_cmd->redir[r])
				{
					change_inf(mini->s_cmd->redir[r], mini->s_cmd->file[r]);
					change_out(mini->s_cmd->redir[r], mini->s_cmd->file[r]);
					r++;
				}
			}
			if (dup2(mini->s_cmd->fd_stdout, STDOUT_FILENO) == -1)
				message_perror("Error restoring stdout");
			if (dup2(mini->s_cmd->fd_stdin, STDIN_FILENO) == -1)
				message_perror("Error restoring stdin");
		}
		else if (mini->s_cmd->cmd_arg[0] == NULL)
		{

		}
		else if (isbuildin(mini->s_cmd->cmd_arg[0]) == 0)
		{

		}
		else
// le path n<est pas encore set//
		
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
		n++;
	}
	return (0);
}

int	time_to_execute(t_minishell *mini)
{
	int		i;
	int		total_cmd;

	i = 0;
	mini->s_cmd = ft_calloc(1, sizeof(t_cmd));
	initialize_scmd(mini);
	all_here_doc2(mini);
	forker2(mini);
	while (i < mini->token_count)
	{
		waitpid(mini->s_cmd->pids[i], &mini->s_cmd->status, 0);
		mini->s_cmd->c++;
	}
	free(mini->s_cmd->pids);
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