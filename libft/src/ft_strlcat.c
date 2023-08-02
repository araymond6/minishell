/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:26:48 by araymond          #+#    #+#             */
/*   Updated: 2023/01/20 14:14:03 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;
	size_t	dstlen;
	size_t	copylen;

	if (!dst || !src)
		return (0);
	srclen = ft_strlen(src);
	i = dstsize;
	while (*dst && i > 0)
	{
		dst++;
		i--;
	}
	dstlen = dstsize - i;
	if (dstlen < dstsize)
	{
		copylen = i - 1;
		if (srclen < copylen)
			copylen = srclen;
		ft_memcpy(dst, src, copylen);
		dst[copylen] = '\0';
	}
	return (srclen + dstlen);
}
