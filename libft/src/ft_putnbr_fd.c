/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:36:59 by araymond          #+#    #+#             */
/*   Updated: 2023/01/20 14:13:50 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_create(long a, char *number, int i)
{
	int		j;
	char	fullnum[15];

	j = 0;
	if (a < 0)
	{
		number[0] = '-';
		a = -a;
		j++;
	}
	while (a)
	{
		fullnum[i++] = a % 10 + 48;
		a /= 10;
	}
	i--;
	while (i >= 0)
		number[j++] = fullnum[i--];
	number[j] = '\0';
}

static char	*ft_itoa2(int n, char *number)
{
	long	a;

	a = n;
	if (a == 0)
	{
		number[0] = '0';
		number[1] = '\0';
		return (number);
	}
	if (!number)
		return (NULL);
	ft_create(a, number, 0);
	return (number);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	i;
	char			nb[12];

	ft_itoa2(n, nb);
	i = write(fd, nb, ft_strlen(nb));
}
