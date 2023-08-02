/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:22:22 by araymond          #+#    #+#             */
/*   Updated: 2023/01/20 14:14:16 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	a;

	if (!s)
		return (NULL);
	a = c;
	i = ft_strlen(s);
	while (i > 0 && s[i] != a)
		i--;
	if (s[i] == a)
		return ((char *)s + i);
	else
		return (NULL);
}
