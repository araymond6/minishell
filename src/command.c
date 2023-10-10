#include "../include/minishell.h"



//s_cmd : attribute values for cmd, path, and, arg_cmd
int	check_command(t_minishell *mini, int i, int j)
{
	int	k;

	k = 1;
	j = s_cmd_cmd(mini, i, j);
	if (find_path(mini) == -1)
		return (-1);
	mini->s_cmd->narg = nbr_arg(mini, i, j);
	mini->s_cmd->cmd_arg = ft_calloc(mini->s_cmd->narg + 2, sizeof(char *));
	if (mini->cmd[i][j] == ' ')
		j++;
	if (!mini->s_cmd->cmd_arg || s_cmd_arg_cmd_first(mini) == -1)
		return (-1);
	if (mini->s_cmd->narg > 0)
	{
		while (k < mini->s_cmd->narg)
		{
			j = s_cmd_arg_cmd_middle(mini, i, j, k);
			if (j == -1)
				return (-1);
			k++;
		}
		j = s_cmd_arg_cmd_end(mini, i, j, k);
	}
	return (j);
}
