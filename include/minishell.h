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
# include <curses.h>
# include <sys/ioctl.h>
# include <string.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "../libft/src/libft.h"
# include <limits.h>

typedef struct s_cmd
{
	int				*redir;
	char			*cmd;
	char			*path;
	char			**cmd_arg;
	char			**file;
	int				nredir;
	int				*pipe;
	int				narg;
	int				*status;
	int				fd_stdin;
	int				fd_stdout;
	int				qlen;
	int				c;
	int				*new_cmd;
	int				*pids;
}	t_cmd;


typedef enum e_type
{
	WHITESPACE = 0, // space, tabs or newlines
	STRING = 1, // words or letters
	PIPE = 2, // |
	DOLLAR_SIGN = 3, // $
	SINGLE_QUOTE = 4, // '
	DOUBLE_QUOTE = 5, // "
	APPEND = 6, // >>
	HERE_DOC = 7, // <<
	REDIRECT_OUTPUT = 8, // >
	REDIRECT_INPUT = 9, // <
}	t_type;

typedef struct s_token
{
	char	*token;
	size_t	len;
	t_type	type;
	char	inquote;
	char	indoublequote;
	int		no_cmd;
}	t_token;

typedef struct s_parse
{
	int		block_count;
	int		c;
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
	int					envpset;
	struct s_token		*token;
	int					token_count;
	struct s_parse		parse;
	struct sigaction	sigact;
	struct s_cmd		*s_cmd;
	unsigned char		exit_code;
	char				*heredoc_flag;
	int					heredoc_count;
	int					count;
	int					total_cmd;
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
int		execute_cmd(t_minishell *mini);
int		parent(t_cmd *cmd);
int		child(t_minishell *mini);
int		process(t_minishell *mini);

//here_doc.c
int		here_doc(t_minishell *mini, char *delimiter);
int		set_flag(t_minishell *mini);
char	*heredoc_count(t_minishell *mini, char *new_line);

//parsing_exec.c
int		parsing_command(t_minishell *mini, int i);
int		create_list(t_minishell *mini);

//path.c
void	join_path_command(char **path, char *command);
char	*test_path(char **path);
int		find_path(t_minishell *mini);

//redirections.c
int		redir_count(t_minishell *mini, char *cmd);
int		redirection(t_minishell *mini, int i, int j, char c);
int		select_redirection(t_minishell *mini, int i, int j);

//s_cmd_attribution.c
void	initialize_s_cmd(t_minishell *mini);
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
int		doublequote_parse(t_minishell *mini, int *i);
void	quote_parse(t_minishell *mini, int *i);
int		count_sub_dollar(t_minishell *mini, int *i);
int		get_block(t_minishell *mini);
int		doublequote_cmd(t_minishell *mini, int *i, int *j);
void	quote_cmd(t_minishell *mini, int *i, int *j);
void	parse_exit(t_minishell *mini);
int		sub_dollar(t_minishell *mini, int *i, int *j, char *str);
int		add_sub_env(t_minishell *mini, char *arg);
int		add_from_env(t_minishell *mini, int *j, char *arg, char *str);
void	add_exitcode(int *j, char *arg, char *str);
int		quote_check(t_minishell *mini, int *i);
int		special_char_check(t_minishell *mini, int *i);
int		redir_parsing(t_minishell *mini);
char	*env_parsing(t_minishell *mini, int *i, int *j);

//errors
void	parsing_error(t_minishell *mini);
void	malloc_error(t_minishell *mini, char **to_free);

//utils
void	initialize_mini(t_minishell *mini, char **envp);
void	clear_mini(t_minishell *mini);
void	exit_program(t_minishell *mini);
char	*check_env(t_minishell *mini, char *arg);
void	signal_handler(int signal);
void	sigint_handler(int signal);
void	free_array(char **array);
int		len_until_space(t_minishell *mini, int i, int j);
int		len_until_redirections(t_minishell *mini, int i, int j);
int		ft_strjcpy(char *dst, char *src, int max, int j);
int		message_perror(char *str);
int		count_2darray(char **table);
int		spacentabs_check(char *str);
void	set_signal_for_process(t_minishell *mini);
void	signal_reset(t_minishell *mini);

// buildins and start of exec
int		x_comm(t_minishell *mini);
int		ft_cd(t_cmd *cmd);
int		ft_pwd(void);
int		ft_cd(t_cmd *cmd);
int		ft_echo(t_cmd *cmd);
int		ft_env(t_minishell *mini);
int		ft_export(t_minishell *mini);
int		ft_unset(t_minishell *mini);
int		while_table(t_minishell *mini, int *j, int *c, char **table);
int		set_table(t_minishell *mini, char **table, int *j, int *k);
void	free_scmd(t_cmd *cmd);
int		count_quote(char *cmd, int i);
int		ft_exit(t_minishell *mini);
int		file_n_redir_calloc(t_minishell *mini, int c);
int		forker(int n, int *pids, t_minishell *mini);
void	print_env(t_minishell *mini);
int		count_quote2(char *cmd, int i);
void	all_here_doc(t_minishell *mini);
int		forker(int n, int *pids, t_minishell *mini);
int		to_fork(t_minishell *mini, int *pids, int n);
int		child(t_minishell *mini);
int		parent(t_cmd *cmd);
int		ft_atoll(const char *str);
int		quote_jump(char *cmd, int i, char c);
int		redirection_jump(t_minishell *mini, char *cmd, int i, char c);
int		redir_quote(t_minishell *mini, int i, int j, int r);

//new functions Valerie
void	nb_carg(t_minishell *mini, int n);
void	cpy_cmd(t_minishell *mini, int n, int i);
void	find_cmd(t_minishell *mini, int n);
int		null_command2(t_minishell *mini, int n);
void	exec_buildin2(t_minishell *mini, int n);
void	redirect_input(t_minishell *mini, int i);
void	redirect_here_doc(void);
void	redirect_output(t_minishell *mini, int i);
void	redirect_append(t_minishell *mini, int i);
void	manual_redirection(t_minishell *mini, int n);
void	all_here_doc2(t_minishell *mini);
void	clear_s_cmd(t_cmd *cmd);
void	join_path_command2(char **path, char *command);
char	*test_path2(char **path);
void	find_path2(t_minishell *mini);
void	child_redirection(t_minishell *mini, int n);
void	child_path(t_minishell *mini);
char	*child_path_execve(char *string);
char	**child_array_execve(char **array);
void	child_closenfree(t_minishell *mini);
void	execve_failed(char *path_execve, char **array_execve);
void	child2(t_minishell *mini, int n);
int		parent2(t_minishell *mini, int n);
void	exec_bash_cmd(t_minishell *mini, int n);
int		forker2(t_minishell *mini);
int		time_to_execute(t_minishell *mini);

#endif