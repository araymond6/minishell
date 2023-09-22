/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:20 by araymond          #+#    #+#             */
/*   Updated: 2023/09/22 14:58:34 by vst-pier         ###   ########.fr       */
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

//TODO check diffrence and change for the aurelias env
typedef struct s_cmd
{
	char			*redir;
	char			*cmd;
	char			*path;
	char			**cmd_arg;
	char			**file;			
	struct s_cmd	*next;
	int				nredir;	
	struct s_cmd	*prev;
	int				pipe_fd[2];
	int				narg;		
	int				status;	
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
	struct s_cmd		*s_cmd;
	int					exit_code;
}	t_minishell;

//build-in.c
int		isbuildin(char *isbuildin);
int		execute_buildin(t_cmd *cmd);

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
//parsing
void	read_input(t_minishell *mini);
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
void	free_array(char **array);
int		len_until_space(t_minishell *mini, int i, int j);
int		len_until_redirections(t_minishell *mini, int i, int j);
int		ft_strjcpy(char *dst, char *src, int max, int j);
int		message_perror(char *str);

int	x_comm(t_minishell *mini);
int	ft_cd(t_cmd *cmd);
int	ft_pwd(t_cmd *cmd);


#endif