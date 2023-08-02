/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:50:26 by araymond          #+#    #+#             */
/*   Updated: 2023/01/19 15:54:20 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*pass;
	t_list	*temp;

	if (lst)
	{
		if (*lst)
		{
			pass = *lst;
			while (pass)
			{
				del(pass->content);
				temp = pass;
				pass = pass->next;
				free(temp);
			}
			*lst = NULL;
		}
	}
}
