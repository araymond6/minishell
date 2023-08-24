/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerie <valerie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:45:48 by vst-pier          #+#    #+#             */
/*   Updated: 2023/08/24 14:50:40 by valerie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//function qui parse la ligne de commande
void parsing_command(t_minishell *mini, int i)
{
	//t_cmd *command;
	int j;
	t_cmd *command;
	j = 0;
	if(!mini->struct_cmd)
	{
		mini->struct_cmd = ft_calloc(1, sizeof(t_cmd));
		initialize_struct_cmd(mini->struct_cmd);
	}
	if(!mini->struct_cmd->next)
	{
		mini->struct_cmd->next = ft_calloc(1, sizeof(t_cmd));
		initialize_struct_cmd(mini->struct_cmd->next);
	}
	mini->struct_cmd->nb_redir = redir_count(mini->cmd[i]);
	while(mini->cmd[i][j] && mini->cmd[i])
	{
		if(mini->cmd[i][j] == '<')
			j = entry_redirection(mini, i, j + 1);
		else if(mini->cmd[i][j] == '>')
			j = exit_redirection(mini, i, j + 1);
		else if(mini->cmd[i][j] == ' ')
			j++;
		else
			j = check_command(mini, i, j);
	}
}

// function qui trie larray mini->cmd pour completer la structure struct_cmd;
void create_list(t_minishell *mini)
{
	int i;
	t_cmd *copy;
	
	i = 0;
	copy = ft_calloc(1, sizeof(t_cmd));
	while(mini->cmd[i] != NULL)
	{
		parsing_command(mini, i);
		copy = mini->struct_cmd;
		mini->struct_cmd = mini->struct_cmd->next;
		mini->struct_cmd->prev = copy;
		i++;
	}
	while (i-- > 0)
		mini->struct_cmd = mini->struct_cmd->prev;
}

int	message_perror_b(char *str)
{
	perror(str);
	return (EXIT_FAILURE);
}

int change_inf(t_cmd *cmd, char c, char *file)
{
	int fd;
	
	if(c == '1')
	{
		fd = open(file, O_RDONLY);
		if(fd == -1)
			return(message_perror_b("ERROR"));
		dup2(fd, STDIN_FILENO);
	}
	else if(c == '2')     //TODO changer pour un here doc et non une entree standard
	{
		fd = open(file, O_RDONLY);
		if(fd == -1)
			return(message_perror_b("ERROR"));
		dup2(fd, STDIN_FILENO);
	}
	close(fd);
	return(0);
}

int change_out(t_cmd *cmd, char c, char *file)
{
	
	int fd;

	if(c == '3')
	{
		fd = open(file, O_WRONLY, O_CREAT, O_TRUNC, 0644);
		if(fd == -1)
			return(message_perror_b("ERROR"));
		dup2(fd, STDOUT_FILENO);
	}
	else if(c == '4')
	{
		fd = open(file, O_WRONLY, O_CREAT, O_APPEND, 0644);
		if(fd == -1)
			return(message_perror_b("ERROR"));
		dup2(fd, STDOUT_FILENO);
	}
	close(fd);
	return(0);
}

int execute_buildin()
{
	
}

int execute_execve()
{
	
}

int execute_cmd_buildin(t_cmd *cmd)
{
	if(isbuildin(cmd->cmd_arg[0]) == 0)
		execute_buildin();
	else 
		execute_execve();
	return(0);
}

int execution(t_cmd *cmd)
{
	pid_t pid;
	int status;
	int	fd_pipe[2];
	int i;
	
	pid = 1;
	status = 0;
	// dans pipex j'avais mis pipe() dans le while. pourquoi? est-ce mieux?
	if (pipe(fd_pipe) == -1)
		exit(message_perror_b("Problem "));
	while (cmd->next)
	{
		if(pid != 0)
		{
			pid = fork();
			if (pid == -1)
				exit(message_perror_b("Error"));
			i = 0;
			if (pid == 0)
			{
				if(cmd->prev->cmd != NULL)
					dup2(fd_pipe[0], STDIN_FILENO);
				if(cmd->next->cmd != NULL)
					dup2(fd_pipe[1], STDOUT_FILENO);
				while(cmd->redir[i])
				{
					change_inf(cmd, cmd->redir[i], cmd->file[i]);
					change_out(cmd, cmd->redir[i], cmd->file[i]);
					i++;
				}
				execute_cmd_buildin(cmd);
			}
			printf("pid -> %d cmd -> %s\n", pid, cmd->cmd);
			cmd = cmd->next;
		}
	}
	waitpid(pid, &status, 0);
	return(0);
}

//cd echo pwd export unset env exit build-in a re-coder !!!
int main(int argc, char **argv, char **envp)
{
	t_minishell *mini;
	
	(void) argc;
	(void) argv;
	mini = ft_calloc(1, sizeof(t_minishell));
	save_path(mini, envp);
	mini->arg = NULL;
	mini->cmd = ft_calloc(4, sizeof(char*));
	mini->cmd[0] = ft_calloc(28, sizeof(char));
	mini->cmd[0] = "< Makefile /bin/ls -la";
	mini->cmd[1] = ft_calloc(16, sizeof(char));
	mini->cmd[1] = "echo allo";
	mini->cmd[2] = ft_calloc(15, sizeof(char));
	mini->cmd[2] = "wc -l > test.txt";
	mini->cmd[3] = ft_calloc(1, sizeof(char));
	mini->cmd[3] = NULL;
	mini->struct_cmd = NULL;
	create_list(mini);
	execution(mini->struct_cmd);
}