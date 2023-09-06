/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerie <valerie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:45:48 by vst-pier          #+#    #+#             */
/*   Updated: 2023/09/06 15:46:50 by valerie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//function qui parse la ligne de commande
void	parsing_command(t_minishell *mini, int i)
{
	int		j;
	t_cmd	*command;

	j = 0;
	if (!mini->struct_cmd)
	{
		mini->struct_cmd = ft_calloc(1, sizeof(t_cmd));
		initialize_struct_cmd(mini->struct_cmd);
	}
	if (!mini->struct_cmd->next)
	{
		mini->struct_cmd->next = ft_calloc(1, sizeof(t_cmd));
		initialize_struct_cmd(mini->struct_cmd->next);
	}
	mini->struct_cmd->nb_redir = redir_count(mini->cmd[i]);
	while (mini->cmd[i][j] && mini->cmd[i])
	{
		if (mini->cmd[i][j] == '<')
			j = entry_redirection(mini, i, j + 1);
		else if (mini->cmd[i][j] == '>')
			j = exit_redirection(mini, i, j + 1);
		else if (mini->cmd[i][j] == ' ')
			j++;
		else
			j = check_command(mini, i, j);
	}
}

// function qui trie larray mini->cmd pour completer la structure struct_cmd;
void	create_list(t_minishell *mini)
{
	int		i;
	t_cmd	*copy;

	i = 0;
	copy = ft_calloc(1, sizeof(t_cmd));
	while (mini->cmd[i] != NULL)
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

//attention ajouter le parsing de Aure pour ce qui sera lu dans le here_doc
int	here_doc(t_cmd *cmd, char *delimiter)
{
	int	fd;
	char *new_line;
	
	new_line = NULL;
	fd = open("here_doc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (message_perror("2"));
	while(1)
	{
		new_line = readline("\033[92mHERE_DOC > % \033[0m");
		if (!new_line)
			return (message_perror("2.1"));
		else if (ft_strncmp(delimiter, new_line, ft_strlen(delimiter)) == 0)
		{	
			free(new_line);
			break;
		}
		else
		{
			write(fd, new_line, strlen(new_line));
			write(fd, "\n", 1);
		}
		free(new_line);		
	}
	close(fd);
	fd = open("here_doc.txt", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	change_inf(t_cmd *cmd, char c, char *file)
{
	int	fd;

	if (c == '1')
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			return (message_perror("1"));
		dup2(fd, STDIN_FILENO);
	}
	else if (c == '2')
	{
		if(here_doc(cmd, file) == -1)
			return (message_perror("2"));
	}
	close(fd);
	return (0);
}

int	change_out(t_cmd *cmd, char c, char *file)
{
	int	fd;

	if (c == '3')
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (message_perror("3"));
		dup2(fd, STDOUT_FILENO);
	}
	else if (c == '4')
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (message_perror("4"));
		dup2(fd, STDOUT_FILENO);
	}
	close(fd);
	return (0);
}

int	execute_buildin(void)
{
	return (0);
}

int	execute_execve(t_cmd *cmd)
{
	if (execve(cmd->path, cmd->cmd_arg, NULL) == -1)
		return (message_perror("EXECVE"));
	return (0);
}

int	execute_cmd_buildin(t_cmd *cmd)
{
	if (isbuildin(cmd->cmd_arg[0]) == 0)
		execute_buildin();
	else
		execute_execve(cmd);
	return (0);
}

int	execution(t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	int		fd_pipe[2];
	int		i;

	pid = 1;
	status = 0;
	while (cmd->next)
	{
		if (pipe(fd_pipe) == -1)
			exit(message_perror("Pipe"));
		if (pid != 0)
		{
			pid = fork();
			if (pid == -1)
				exit(message_perror("Fork"));
			i = 0;
			if (pid == 0)
			{
				if (cmd->prev->cmd != NULL)
					dup2(fd_pipe[0], STDIN_FILENO);
				if (cmd->next->cmd != NULL)
					dup2(fd_pipe[1], STDOUT_FILENO);
				if (cmd->redir)
				{
					while (cmd->redir[i])
					{
						change_inf(cmd, cmd->redir[i], cmd->file[i]);
						change_out(cmd, cmd->redir[i], cmd->file[i]);
						i++;
					}
				}
				close(fd_pipe[0]);
				close(fd_pipe[1]);
				execute_cmd_buildin(cmd);
			}
			if (pid != 0)
			{
				if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
					exit(EXIT_FAILURE);
				close(fd_pipe[0]);
				close(fd_pipe[1]);
			}
			cmd = cmd->next;
		}
	}
	//on free le contenu de toutes les nodes et les nodes
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 1)
		message_perror("WEXITSTATUS");
	return (0);
}

//cd echo pwd export unset env exit build-in a re-coder !!!
int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;

	(void) argc;
	(void) argv;
	mini = ft_calloc(1, sizeof(t_minishell));
	save_path(mini, envp);
	mini->arg = NULL;
	mini->cmd = ft_calloc(4, sizeof(char *));
	mini->cmd[0] = ft_calloc(28, sizeof(char));
	mini->cmd[0] = "<< END wc -l";
	mini->cmd[1] = ft_calloc(1, sizeof(char));
	mini->cmd[1] = NULL;
	mini->struct_cmd = NULL;
	create_list(mini);
	execution(mini->struct_cmd);
}
