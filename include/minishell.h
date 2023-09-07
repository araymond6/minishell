/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerie <valerie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:20 by araymond          #+#    #+#             */
/*   Updated: 2023/09/07 16:34:29 by valerie          ###   ########.fr       */
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
	char			*redir;
	char			*cmd;
	char			*path;
	char			**cmd_arg;
	char			**file;
	struct s_cmd	*next;
	int				nb_redir;
	struct s_cmd	*prev;
	int				pipe_fd[2];
}	t_cmd;

typedef struct s_minishell
{
	char			*path_envp;
	char			*arg;
	char			**cmd;
	struct s_cmd	*struct_cmd;
}	t_minishell;


void	save_path(t_minishell *mini, char **envp);	
void	create_redir_file(t_minishell *mini);
void	assign_redir_values(t_minishell *mini, char c);
int		entry_redirection(t_minishell *mini, int i, int j);
int		exit_redirection(t_minishell *mini, int i, int j);
int		check_command(t_minishell *mini, int i, int j);
int		redirection1234(t_minishell *mini, int i, int j, char c);
void	initialize_struct_cmd(t_cmd *struct_cmd);
int		len_until_space(t_minishell *mini, int i, int j);
int		redir_count(char *cmd);
void	parsing_command(t_minishell *mini, int i);
int		len_until_redirections(t_minishell *mini, int i, int j);
void	free_array(char **array);
int 	ft_strjcpy(char *dst, char *src, int max, int j);
int		message_perror(char *str);
int		isbuildin(char *isbuildin);
#endif