/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:20 by araymond          #+#    #+#             */
/*   Updated: 2023/08/01 16:32:59 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define ERROR 1
# define SUCCESS 0
# define READLINE_LIBRARY

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <string.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "../libft/src/libft.h"

typedef struct s_cmd
{
	char			*cmd;
	char			**arg;
	char			*infile;
	char			*outfile;
}	t_cmd;

typedef struct s_minishell
{
	char	*path_envp;
	char	*arg;
	char	**cmd;
}	t_minishell;

#endif