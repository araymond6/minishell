/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:13:36 by araymond          #+#    #+#             */
/*   Updated: 2023/10/27 14:30:34 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *arg, size_t og_len, size_t new_len)
{
	void	*new;

	new = NULL;
	if (new_len == 0)
		return (free(arg), NULL);
	else if (!arg)
		return (ft_calloc(new_len + 1, sizeof(char)));
	else if (new_len <= og_len)
		return (arg);
	else
	{
		new = ft_calloc(new_len + 1, sizeof(char));
		if (new)
		{
			ft_memcpy(new, arg, og_len);
			free(arg);
		}
		return (new);
	}
}
