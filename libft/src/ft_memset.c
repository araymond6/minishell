/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:46:23 by araymond          #+#    #+#             */
/*   Updated: 2023/01/20 14:13:43 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	a;
	char	*str;
	size_t	i;

	if (!b)
		return (NULL);
	a = c;
	str = b;
	i = 0;
	while (i < len)
		str[i++] = a;
	return (b);
}
