#include "../include/minishell.h"

static char	*heredoc_sub(t_minishell *mini, char *new_line)
{
	char	*new_sub;
	int		j;
	int		i;
	int		error;

	new_sub = ft_calloc(ft_strlen(mini->arg) + 1 + mini->parse.sub, sizeof(char));
	if (!new_sub)
		return (NULL);
	i = 0;
	j = 0;
	error = 0;
	while (mini->arg[i])
	{
		if (mini->arg[i] == '$')
			error = sub_dollar(mini, &i, &j, new_sub);
		else
			new_sub[j++] = mini->arg[i++];
		if (error == 1)
			return (free(new_sub), NULL);
	}
	free(new_line);
	mini->arg = NULL;
	return (new_sub);
}

char	*heredoc_substitution(t_minishell *mini)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen(mini->arg) + 1, sizeof(char));
	if (!new)
	while (mini->arg[i])
	{
		if (mini->arg[i] == '$')
		{
			//heredoc_sub // TODO: finish heredoc substitution
		}
		else
		{
			new[j] = mini->arg[i];
		}
		i++;
	}
	return (new);
}