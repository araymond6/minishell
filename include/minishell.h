/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:20 by araymond          #+#    #+#             */
/*   Updated: 2023/08/24 14:48:22 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define ERROR 1
# define SUCCESS 0

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
# include <curses.h>
# include <sys/ioctl.h>
# include <string.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "../libft/src/libft.h"

typedef struct s_cmd
{
	char	*cmd;
	char	**arg;
	char	*infile;
	char	*outfile;
}	t_cmd;

typedef struct s_parse
{
	int		sub;
}	t_parse;

typedef struct s_minishell
{
	char				*path_envp;
	char				*arg;
	char				**cmd;
	char				**envp;
	struct s_parse		parse;
	struct sigaction	sigact;
}	t_minishell;

//global exit status, for the $? exception and more
int		EXIT_CODE;

//parsing
int		read_input(t_minishell *mini);
void	doublequote_parse(t_minishell *mini, int *i);
void	quote_parse(t_minishell *mini, int *i);
void	count_sub_dollar(t_minishell *mini, int *i);
void	parsing_error(t_minishell *mini);
void	parse_exit(t_minishell *mini);

//execution

//utils
void	initialize_mini(t_minishell *mini, char **envp);
void	free_mini(t_minishell *mini);
void	exit_program(t_minishell *mini);
int		check_env(t_minishell *mini, char *arg);
void	signal_handler(int signal);

#endif