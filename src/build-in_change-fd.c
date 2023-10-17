#include "../include/minishell.h"

int	change_inf(char c, char *file)
{
	int	fd;

	if (c == '1')
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			return (message_perror("1"));
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (c == '2')
	{
		fd = open("here_doc.txt", O_RDONLY);
		if (fd == -1)
			return (message_perror("2"));
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	change_out(char c, char *file)
{
	int	fd;

	if (c == '3')
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (message_perror("3"));
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (c == '4')
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (message_perror("4"));
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	isbuildin(char *isbuildin)
{
	if (ft_strncmp(isbuildin, "echo", 5) == 0
		|| ft_strncmp(isbuildin, "cd", 3) == 0
		|| ft_strncmp(isbuildin, "pwd", 4) == 0
		|| ft_strncmp(isbuildin, "export", 7) == 0
		|| ft_strncmp(isbuildin, "unset", 6) == 0
		|| ft_strncmp(isbuildin, "env", 4) == 0
		|| ft_strncmp(isbuildin, "exit", 5) == 0)
		return (0);
	return (1);
}

int	execute_buildin(t_minishell *mini)
{
	if (ft_strncmp(mini->s_cmd->cmd_arg[0], "echo", 5) == 0)
		return (ft_echo(mini->s_cmd));
	else if (ft_strncmp(mini->s_cmd->cmd_arg[0], "cd", 3) == 0)
		return (ft_cd(mini->s_cmd));
	else if (ft_strncmp(mini->s_cmd->cmd_arg[0], "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(mini->s_cmd->cmd_arg[0], "export", 7) == 0)
		return (ft_export(mini));
	else if (ft_strncmp(mini->s_cmd->cmd_arg[0], "env", 4) == 0)
		return (ft_env(mini));
	else if (ft_strncmp(mini->s_cmd->cmd_arg[0], "unset", 6) == 0)
		return (ft_unset(mini));
	else if (ft_strncmp(mini->s_cmd->cmd_arg[0], "exit", 5) == 0)
		ft_exit(mini);
	return (0);
}
