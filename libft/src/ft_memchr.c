/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:45:14 by araymond          #+#    #+#             */
/*   Updated: 2023/01/20 14:13:34 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	a;
	char	*str;
	size_t	i;

	if (!s || n == 0)
		return (NULL);
	str = (char *)s;
	a = c;
	i = 0;
	while (str[i] != a && --n > 0)
		i++;
	if (str[i] == a)
		return ((void *)&str[i]);
	else
		return (NULL);
}
