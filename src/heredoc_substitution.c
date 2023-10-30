#include "../include/minishell.h"

static char	*heredoc_get_env(t_minishell *mini, char *sub)
{
	char	*temp;

	if (!sub)
		return (NULL);
	if (sub[0] == '?')
	{
		free(sub);
		sub = get_exit_code(mini);
		if (!sub)
			return (malloc_error(mini, NULL), NULL);
	}
	else
	{
		temp = sub;
		sub = check_env(mini, temp);
		free(temp);
		if (!sub)
			return (malloc_error(mini, NULL), NULL);
	}
	return (sub);
}

static char	*heredoc_get_sub(t_minishell *mini, int *i)
{
	char	*sub;
	int		j;

	j = 0;
	sub = ft_calloc(ft_strlen(&mini->arg[*i]) + 1, sizeof(char));
	if (!sub)
		return (malloc_error(mini, NULL), NULL);
	while ((ft_isalnum(mini->arg[*i]) || mini->arg[*i] == '?' || mini->arg[*i] == '_') && mini->arg[*i])
	{
		sub[j++] = mini->arg[(*i)++];
		if ((mini->arg[*i] == '?') || sub[0] == '?')
			break ;
		printf("sub: %s\n", sub);
	}
	if (sub[0] == '\0')
		return (free(sub), NULL);
	return (sub);
}

static char	*heredoc_sub(t_minishell *mini, char *new, int *i)
{
	char	*sub;
	char	*temp;
	int		j;
	
	j = 0;
	sub = heredoc_get_sub(mini, i);
	sub = heredoc_get_env(mini, sub);
	if (!sub)
		return (NULL);
	if (ft_strchr(sub, '='))
	{
		while (sub[j] != '=')
			j++;
		j++;
	}
	temp = new;
	new = ft_strjoin(temp, &sub[j]);
	free(temp);
	free(sub);
	if (!new)
		return (malloc_error(mini, NULL), NULL);
	return (new);
}

char	*heredoc_substitution(t_minishell *mini, char *new_line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	mini->arg = new_line;
	new = ft_calloc(ft_strlen(mini->arg) + 1, sizeof(char));
	if (!new)
		return (malloc_error(mini, NULL), NULL);
	while (mini->arg[i])
	{
		if (mini->arg[i] == '$')
		{
			i++;
			new = heredoc_sub(mini, new, &i);
			if (!new)
				return (NULL);
			new = ft_realloc(new, ft_strlen(new), ft_strlen(new) \
			+ ft_strlen(&mini->arg[i]) + 1);
			j = ft_strlen(new);
		}
		else
			new[j++] = mini->arg[i++];
	}
	return (new);
}