#include "../include/minishell.h"

int	ft_pwd(void)
{
	char	absolute_path[200];

	if (getcwd(absolute_path, 200) == NULL)
		return (message_perror("pwd :"));
	printf("%s\n", absolute_path);
	return (0);
}

int	ft_cd(t_cmd *cmd)
{
	if (cmd->cmd_arg[2])
		return (message_perror("Too many arguments"));
	if (chdir(cmd->cmd_arg[1]) == -1)
		return (message_perror("cd : "));
	return (0);
}

void	p_echo(char **str, int r, int n)
{
	int	i;

	i = 0;
	while (str[r] != NULL)
	{
		while (str[r][i])
		{
			write(1, &str[r][i], 1);
			i++;
		}
		i = 0;
		if (str[++r])
			write(1, " ", 1);
	}
	if (n == 0 || n == 2)
		write(1, "\n", 1);
}

int	ft_echo(t_cmd *cmd)
{
	int	r;
	int	i;
	int	n;

	r = 1;
	i = 2;
	n = 0;
	if (!cmd->cmd_arg[r])
		return (printf("\n"), 0);
	while (ft_strncmp(cmd->cmd_arg[r], "-n", 2) == 0 && n != 2)
	{
		while (cmd->cmd_arg[r][i] == 'n')
			i++;
		if (cmd->cmd_arg[r][i] == 0)
		{
			r++;
			n = 1;
		}
		else
			n = 2;
		i = 2;
	}
	p_echo(cmd->cmd_arg, r, n);
	return (0);
}
