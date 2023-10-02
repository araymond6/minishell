#include "../include/minishell.h"

//free an array
void	free_array(char **array)
{
	int	index_array;

	index_array = 0;
	if(!array)
		return;
	while (array[index_array])
	{
		free(array[index_array]);
		array[index_array] = NULL;
		index_array++;
	}
	free(array);
	array = NULL;
}

//count the nbr of char before the next space
int	len_until_space(t_minishell *mini, int i, int j)
{
	int	len;

	len = 0;
	while (mini->cmd[i][j + len] != ' ' && mini->cmd[i][j + len] != '>'
		&& mini->cmd[i][j + len] != '<' && mini->cmd[i][j + len])
		len++;
	return (len);
}

//count the nbr of char before the next redirection < or >
int	len_until_redirections(t_minishell *mini, int i, int j)
{
	int	len;

	len = 0;
	while (mini->cmd[i][j + len] != '<'
		&& mini->cmd[i][j + len] != '>' && mini->cmd[i][j + len])
		len++;
	return (len);
}

//copy from the position j for maximum max char
int	ft_strjcpy(char *dst, char *src, int max, int j)
{
	int	i;

	i = 0;
	while (i < max)
	{
		dst[i] = src[j + i];
		i++;
	}
	return (j + i);
}

//write the error code after str
int	message_perror(char *str)
{
	perror(str);
	return (EXIT_FAILURE);
}
