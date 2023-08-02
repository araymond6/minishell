/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:52:48 by araymond          #+#    #+#             */
/*   Updated: 2023/01/20 14:13:39 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*ddst;
	const char	*ssrc;

	ddst = dst;
	ssrc = src;
	i = 0;
	if (n == 0 || !dst || !src)
		return (dst);
	while (i < n)
	{
		ddst[i] = ssrc[i];
		i++;
	}
	return (dst);
}
