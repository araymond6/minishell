/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerie <valerie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:59:37 by valerie           #+#    #+#             */
/*   Updated: 2023/09/11 16:41:36 by valerie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// function who read the entry and put it in the here_doc file
int	read_write(t_cmd *cmd, char *delimiter, int fd)
{
	char	*new_line;
	int		i;

	new_line = readline("\033[92mHERE_DOC > % \033[0m");
	if (!new_line)
		return (message_perror("2.1"));
	else if (ft_strncmp(delimiter, new_line, ft_strlen(delimiter)) == 0)
		i = 1 ;
	else
	{
		write(fd, new_line, strlen(new_line));
		write(fd, "\n", 1);
	}
	free(new_line);
	return (i);
}

// TODO attention ajouter le parsing de Aure pour ce qui sera lu dans le here_doc
// function for the << redirection
int	here_doc(t_cmd *cmd, char *delimiter)
{
	int		fd;
	char	*new_line;
	int		i;

	i = 0;
	new_line = NULL;
	fd = open("here_doc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (message_perror("2"));
	while (i == 0)
		i = read_write(cmd, delimiter, fd);
	close(fd);
	fd = open("here_doc.txt", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}