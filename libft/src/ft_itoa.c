/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:53:39 by araymond          #+#    #+#             */
/*   Updated: 2023/01/23 16:46:53 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_allocate(long a, char *number, int i)
{
	if (a > 0)
	{
		while (a)
		{
			i++;
			a /= 10;
		}
		number = (char *)malloc(sizeof(*number) * i + 1);
	}
	else
	{
		i++;
		a = -a;
		while (a)
		{
			i++;
			a /= 10;
		}
		number = (char *)malloc(sizeof(*number) * i + 1);
	}
	return (number);
}

static char	*ft_create(long a, char *number, int i)
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
	return (number);
}

char	*ft_itoa(int n)
{
	char	*number;
	long	a;

	a = n;
	number = NULL;
	if (a == 0)
	{
		number = (char *)malloc(sizeof(*number) * 2);
		if (!number)
			return (NULL);
		number[0] = '0';
		number[1] = '\0';
		return (number);
	}
	number = ft_allocate(a, number, 0);
	if (!number)
		return (NULL);
	number = ft_create(a, number, 0);
	return (number);
}
