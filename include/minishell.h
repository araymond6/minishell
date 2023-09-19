/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:20 by araymond          #+#    #+#             */
/*   Updated: 2023/09/19 10:53:29 by vst-pier         ###   ########.fr       */
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
	char			*redir;			//ok
	char			*cmd;
	char			*path;
	char			**cmd_arg;
	char			**file;			//ok
	struct s_cmd	*next;
	int				nredir;			//ok
	struct s_cmd	*prev;
	int				pipe_fd[2];		//ok
	int				narg;			//ok
	int				status;			//ok
}	t_cmd;

typedef struct s_minishell
{
	char			*path_envp;
	char			*arg;
	char			**cmd;
	struct s_cmd	*s_cmd;
}	t_minishell;

//build-in.c
int		isbuildin(char *isbuildin);
int		execute_buildin(void);

//change_fd.c
int		change_inf(t_cmd *cmd, char c, char *file);
int		change_out(t_cmd *cmd, char c, char *file);

//command.c 
int		check_command(t_minishell *mini, int i, int j);

//exec.c
int		execute_cmd_buildin(t_cmd *cmd);
int		parent(t_cmd *cmd);
int		child(t_cmd *cmd);
int		process(t_cmd *cmd);

//here_doc.c
int		read_write(t_cmd *cmd, char *delimiter, int fd);
int		here_doc(t_cmd *cmd, char *delimiter);

//parsing_exec.c
int		initialize(t_cmd *cmd);
void	parsing_command(t_minishell *mini, int i);
void	create_list(t_minishell *mini);

//path.c
void	join_path_command(char **path, char *command);
char	*test_path(char **path);
int		find_path(t_minishell *mini);

//redirections.c
int		redir_count(char *cmd);
int		redirection(t_minishell *mini, int i, int j, char c);
void	assign_redir_values(t_minishell *mini, char c);
int		entry_redirection(t_minishell *mini, int i, int j);
int		exit_redirection(t_minishell *mini, int i, int j);

//s_cmd_attribution.c
void	initialize_s_cmd(t_cmd *cmd);
int		s_cmd_cmd(t_minishell *mini, int i, int j);
int		s_cmd_arg_cmd_first(t_minishell *mini, int i, int j);
int		s_cmd_arg_cmd_middle(t_minishell *mini, int i, int j, int k);
int		s_cmd_arg_cmd_end(t_minishell *mini, int i, int j, int k);

//save_path_aurelia.c
void	save_path(t_minishell *mini, char **envp);

//utils_exec_2.c
int		nbr_arg(t_minishell *mini, int i, int j);

//utils_exec.c

void	free_array(char **array);
int		len_until_space(t_minishell *mini, int i, int j);
int		len_until_redirections(t_minishell *mini, int i, int j);
int		ft_strjcpy(char *dst, char *src, int max, int j);
int		message_perror(char *str);

#endif