/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:20 by araymond          #+#    #+#             */
/*   Updated: 2023/09/21 10:59:59 by araymond         ###   ########.fr       */
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
	int		block_count;
	int		c; // holds current count from parse->cmd[c] during parsing
	int		sub;
	int		start_block;
	int		end_block;
}	t_parse;

typedef struct s_minishell
{
	char				*arg;
	char				**cmd;
	char				**envp;
	struct s_parse		parse;
	struct sigaction	sigact;
	int					exit_code;
}	t_minishell;

//parsing
int		read_input(t_minishell *mini);
int		quote_check(t_minishell *mini, int *i);
int		end_doublequote(t_minishell *mini, int *i);
int		end_quote(t_minishell *mini, int *i);
void	doublequote_parse(t_minishell *mini, int *i);
void	quote_parse(t_minishell *mini, int *i);
void	count_sub_dollar(t_minishell *mini, int *i);
void	get_block(t_minishell *mini);
void	doublequote_cmd(t_minishell *mini, int *i, int *j);
void	quote_cmd(t_minishell *mini, int *i, int *j);
void	parse_exit(t_minishell *mini);
void	sub_dollar(t_minishell *mini, int *i, int *j);

//execution

//errors
void	parsing_error(t_minishell *mini);
void	malloc_error(t_minishell *mini);

//utils
void	initialize_mini(t_minishell *mini, char **envp);
void	free_mini(t_minishell *mini);
void	clear_mini(t_minishell *mini);
void	exit_program(t_minishell *mini);
char	*check_env(t_minishell *mini, char *arg);
void	signal_handler(int signal);

#endif