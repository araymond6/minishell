#include "../include/minishell.h"

int ft_cd(t_cmd *cmd)
{
	if(chdir(cmd->cmd_arg[1])== -1)
		return(message_perror("cd : "));
	return(0);
}
