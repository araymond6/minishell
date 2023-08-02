/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:55:31 by araymond          #+#    #+#             */
/*   Updated: 2023/03/07 16:01:06 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzerognl(char *s, size_t n)
{
	size_t	i;
	char	*str;

	if (!s)
		return ;
	i = 0;
	str = s;
	while (i < n)
	{
		if (str[i] != 0)
			str[i] = 0;
		i++;
	}
}

char	*ft_callocgnl(size_t count, size_t size)
{
	char	*s;

	s = (char *)malloc(count * size);
	if (!s)
		return (NULL);
	ft_bzerognl(s, count * size);
	return (s);
}

char	*ft_strjoingnl(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*new;

	if (!s2 || !s1)
		return (NULL);
	new = ft_callocgnl(sizeof(*new), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
		new[i++] = s2[j++];
	free(s1);
	return (new);
}
