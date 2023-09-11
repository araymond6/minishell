/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerie <valerie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:01:58 by valerie           #+#    #+#             */
/*   Updated: 2023/09/11 16:38:21 by valerie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// change the STDIN for the infile if a < or << is in the command line
int	change_inf(t_cmd *cmd, char c, char *file)
{
	int	fd;

	if (c == '1')
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			return (message_perror("1"));
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (c == '2')
	{
		if (here_doc(cmd, file) == -1)
			return (message_perror("2"));
	}
	return (0);
}

// change the STDIN for the infile if a > or >> is in the command line
int	change_out(t_cmd *cmd, char c, char *file)
{
	int	fd;

	if (c == '3')
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (message_perror("3"));
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (c == '4')
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (message_perror("4"));
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}
