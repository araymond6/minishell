/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:32:22 by araymond          #+#    #+#             */
/*   Updated: 2023/09/19 15:22:25 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Sets the memory starting at *s with zero for n bytes.
void	ft_bzero(void *s, size_t n)
{
	// size_t	i;
	// char	*str;

	// i = 0;
	// if (!s)
	// 	return ;
	// str = s;
	// while (i < n)
	// {
	// 	if (str[i] != 0)
	// 		str[i] = 0;
	// 	i++;
	// }
	ft_memset(s, '\0', n);
}
