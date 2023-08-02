/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:58:03 by araymond          #+#    #+#             */
/*   Updated: 2023/01/20 11:18:10 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*ddst;
	const char		*ssrc;
	unsigned int	i;

	if (!dst || !src)
		return (dst);
	ssrc = src;
	ddst = dst;
	i = 0;
	if (len == 0 || (!dst && !src) || ssrc == ddst)
		return (dst);
	while (ddst > ssrc && --len > 0)
	{
		ddst[len] = ssrc[len];
		if (len == 1)
			ddst[0] = ssrc[0];
	}
	while (ssrc > ddst && i < len)
	{
		ddst[i] = ssrc[i];
		i++;
	}
	return (dst);
}
