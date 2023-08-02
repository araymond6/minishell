/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:59:07 by araymond          #+#    #+#             */
/*   Updated: 2023/03/07 16:00:51 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//cleans up the static char to hold the next line
static char	*ft_newstat(char *stat)
{
	int		i;
	int		j;
	char	*newstat;

	i = 0;
	j = 0;
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == '\0')
	{
		free(stat);
		return (NULL);
	}
	i++;
	newstat = ft_callocgnl(sizeof(*newstat), ft_strlen(stat) - i + 1);
	if (!newstat)
	{
		free(stat);
		return (NULL);
	}
	while (stat[i])
		newstat[j++] = stat[i++];
	free(stat);
	return (newstat);
}

//gets the line to return from the static char
static char	*ft_getline(char *stat, char *line)
{
	int	i;

	i = 0;
	if (!stat)
		return (NULL);
	while (stat[i] != '\n' && stat[i])
		i++;
	line = ft_callocgnl(sizeof(*line), i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (stat[i] != '\n' && stat[i])
	{
		line[i] = stat[i];
		i++;
	}
	if (stat[i] == '\n')
		line[i] = stat[i];
	return (line);
}

//checks if rd < 0; if so, frees stat and buf and returns 0
static int	ft_checkrd(char *stat, char *buf, int rd)
{
	if (rd < 0)
	{
		free(stat);
		free(buf);
		return (0);
	}
	return (1);
}

//reads through the file up until \n or EOF
static char	*ft_findnewline(int fd, char *stat)
{
	char	*buf;
	int		rd;

	buf = ft_callocgnl(sizeof(*buf), (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	rd = 1;
	while (rd > 0 && !ft_strchr(buf, '\n'))
	{
		ft_bzerognl(buf, BUFFER_SIZE);
		rd = read(fd, buf, BUFFER_SIZE);
		if (!ft_checkrd(stat, buf, rd))
			return (NULL);
		stat = ft_strjoingnl(stat, buf);
		if (!stat)
			return (NULL);
	}
	if (stat[0] == '\0')
	{
		free(stat);
		stat = NULL;
	}
	free(buf);
	return (stat);
}

//main function: calls other functions
char	*get_next_line(int fd)
{
	char		*line;
	static char	*stat;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0))
	{
		if (stat)
		{
			free(stat);
			stat = NULL;
		}
		return (NULL);
	}
	if (!stat)
	{
		stat = ft_callocgnl(sizeof(*stat), 1);
		if (!stat)
			return (NULL);
	}
	stat = ft_findnewline(fd, stat);
	line = NULL;
	line = ft_getline(stat, line);
	if (!line)
		return (NULL);
	stat = ft_newstat(stat);
	return (line);
}
