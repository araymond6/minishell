#include "../include/minishell.h"

int ft_pwd(t_cmd *cmd)
{
	char	absolute_path[200];

	if (getcwd(absolute_path, 200) == NULL)
		return (message_perror("pwd :"));
	printf("%s\n", absolute_path);
	return(0);
}
