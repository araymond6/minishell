/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 10:16:53 by araymond          #+#    #+#             */
/*   Updated: 2023/10/12 15:12:11 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcopy(char *new, const char *s1, int dstsize)
{
	int	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < (dstsize - 1) && s1[i])
		{
			new[i] = s1[i];
			i++;
		}
	}
}

// Trims the start and the end of the string with the characters in *set
char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*new;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]) && i <= j)
		i++;
	if (i > j)
		return (ft_strdup(s1 + j + 1));
	while (ft_strchr(set, s1[j]) && j >= 0)
		j--;
	k = j - i + 2;
	new = ft_calloc(sizeof(*new), k);
	if (!new)
		return (NULL);
	ft_strcopy(new, &s1[i], k);
	return (new);
}
