#include "../include/minishell.h"

void	count_heredoc(t_minishell *mini)
{
	int	i;

	i = 0;
	while (i < mini->token_count)
	{
		if (mini->token[i].type == HERE_DOC)
			mini->heredoc_count++;
		i++;
	}
}

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

static char	*heredoc_get_sub(t_minishell *mini, int *i, char *new_line)
{
	char	*sub;
	int		j;

	j = 0;
	sub = ft_calloc(ft_strlen(&new_line[*i]) + 1, sizeof(char));
	if (!sub)
		return (malloc_error(mini, NULL), NULL);
	while ((ft_isalnum(new_line[*i]) || new_line[*i] == '?' || \
			new_line[*i] == '_') && new_line[*i])
	{
		sub[j++] = new_line[(*i)++];
		if ((new_line[*i] == '?') || sub[0] == '?')
			break ;
	}
	if (sub[0] == '\0')
		return (free(sub), NULL);
	return (sub);
}

static char	*heredoc_sub(t_minishell *mini, char *new, int *i, char *new_line)
{
	char	*sub;
	char	*temp;
	int		j;

	j = 0;
	sub = heredoc_get_sub(mini, i, new_line);
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
	new = ft_calloc(ft_strlen(new_line) + 1, sizeof(char));
	if (!new)
		return (malloc_error(mini, NULL), NULL);
	while (new_line[i])
	{
		if (new_line[i] == '$')
		{
			i++;
			new = heredoc_sub(mini, new, &i, new_line);
			if (!new)
				return (NULL);
			new = ft_realloc(new, ft_strlen(new), ft_strlen(new) \
			+ ft_strlen(&new_line[i]) + 1);
			j = ft_strlen(new);
		}
		else
			new[j++] = new_line[i++];
	}
	return (new);
}
