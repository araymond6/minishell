/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:28:59 by araymond          #+#    #+#             */
/*   Updated: 2023/02/14 11:29:39 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charcount(char const *s, char c, int *count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i] != c && s[i])
	{
		i++;
		j++;
	}
	*count += i;
	return (j + 1);
}

static char	**ft_create(char const *s, char c, char **new)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		new[j][k++] = s[i];
		i++;
		if (s[i] == c && s[i])
		{
			new[j++][k] = '\0';
			k = 0;
		}
		while (s[i] == c && s[i])
			i++;
		if (!s[i] && s[i - 1] != c)
			new[j++][k] = '\0';
	}
	new[j] = NULL;
	return (new);
}

static char	**ft_allocatewords(char const *s, char c, int wordc, char **new)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < wordc)
	{
		new[i] = (char *)malloc(sizeof(*new[i]) * \
		(ft_charcount(&s[count], c, &count)));
		if (!new[i])
		{
			while (i > 0)
			{
				free(new[i - 1]);
				i--;
			}
			free(new);
			return (NULL);
		}
		i++;
	}
	new = ft_create(s, c, new);
	return (new);
}

// Splits the string *s into multiple strings using the character *c.
char	**ft_split(char const *s, char c)
{
	char	**new;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	while (*s == c && *s)
		s++;
	i = 0;
	j = 0;
	while (s[i])
	{
		i++;
		if (s[i] == c && s[i])
			j++;
		while (s[i] == c && s[i])
			i++;
		if (!s[i] && s[i - 1] != c)
			j++;
	}
	new = (char **)malloc(sizeof(*new) * (j + 1));
	if (!new)
		return (NULL);
	new = ft_allocatewords(s, c, j, new);
	return (new);
}
