/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:07:42 by araymond          #+#    #+#             */
/*   Updated: 2023/01/20 11:18:34 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char	a;

	if (!s)
		return (NULL);
	a = c;
	while (*s && *s != a)
		s++;
	if (*s == a)
		return ((char *)s);
	else
		return (NULL);
}
