#ifndef MINISHELL_H
# define MINISHELL_H
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
# include <readline/readline.h>
# include <readline/history.h>
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
	int				fd_stdin_out[2];
}	t_cmd;

typedef struct s_parse
{
	int		block_count;
	int		c; // remove the funny comment in here somewhere
	int		sub;
	int		start_block;
	int		end_block;
}	t_parse;

typedef struct s_minishell
{
	char				*arg;
	char				*path;
	char				**cmd;
	char				**envp;
	char				**table;
	struct s_parse		parse;
	struct sigaction	sigact;
	struct s_cmd		*s_cmd;
	char				exit_code;
}	t_minishell;

//build-in.c
int		isbuildin(char *isbuildin);
int		execute_buildin(t_minishell *mini);

//change_fd.c
int		change_inf(char c, char *file);
int		change_out(char c, char *file);

//command.c 
int		check_command(t_minishell *mini, int i, int j);

//exec.c
int		execute_cmd_buildin(t_minishell *mini);
int		parent(t_cmd *cmd);
int		child(t_minishell *mini);
int		process(t_minishell *mini);

//here_doc.c
int		read_write(char *delimiter, int fd);
int		here_doc(char *delimiter);

//parsing_exec.c
int		parsing_command(t_minishell *mini, int i);
int		create_list(t_minishell *mini);
int		quote_n_create(t_minishell *mini);

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
int		s_cmd_arg_cmd_first(t_minishell *mini);
int		s_cmd_arg_cmd_middle(t_minishell *mini, int i, int j, int k);
int		s_cmd_arg_cmd_end(t_minishell *mini, int i, int j, int k);

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
int		sub_dollar(t_minishell *mini, int *i, int *j);
void	add_sub_env(t_minishell *mini, char *arg);
void	add_from_env(t_minishell *mini, int *j, char *arg);
int		quote_check(t_minishell *mini, int *i);
void	special_char_check(t_minishell *mini, int *i);
void	add_exitcode(t_minishell *mini, int *j, char *arg);
int		redir_parsing(t_minishell *mini);
//execution
// *surprised pikachu face* THERE'S NOTHING

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
int		count_2darray(char **table);
void	clear_2darrays(t_minishell *mini);

// buildins and start of exec
int		x_comm(t_minishell *mini);
int		ft_cd(t_cmd *cmd);
int		ft_pwd(void);
int		ft_cd(t_cmd *cmd);
int		ft_echo(t_cmd *cmd);
int		ft_env(t_minishell *mini);
int		ft_export(t_minishell *mini);
int		ft_unset(t_minishell *mini);
void	free_scmd(t_cmd *cmd);
int		count_quote(char *cmd, int i);
void	free_scmd(t_cmd *cmd);
void	ft_exit(t_minishell *mini);

#endif