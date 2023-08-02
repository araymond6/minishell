/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:32:22 by araymond          #+#    #+#             */
/*   Updated: 2023/02/10 10:15:15 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Sets the memory starting at *s with zero for n bytes.
void	ft_bzero(void *s, size_t n)
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
