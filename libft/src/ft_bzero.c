/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:32:22 by araymond          #+#    #+#             */
/*   Updated: 2023/10/16 14:30:17 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Sets the memory starting at *s with zero for n bytes.
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
