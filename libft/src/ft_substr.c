/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:53:19 by araymond          #+#    #+#             */
/*   Updated: 2023/01/20 14:14:21 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_overstart(char *new)
{
	new = (char *)malloc(sizeof(*new) * 1);
	if (!new)
		return (NULL);
	new[0] = '\0';
	return (new);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	s_len;
	char			*new;

	if (!s)
		return (NULL);
	new = NULL;
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		new = ft_overstart(new);
		return (new);
	}
	if (len < ft_strlen(&s[start]))
		new = (char *)malloc(sizeof(*new) * (len + 1));
	else
		new = (char *)malloc(sizeof(*new) * (ft_strlen(&s[start]) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len && start < s_len)
		new[i++] = s[start++];
	new[i] = '\0';
	return (new);
}
