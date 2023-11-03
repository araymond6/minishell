#ifndef MINISHELL_H
# define MINISHELL_H
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
	int				pipe[2];
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
	WHITESPACE = 0,
	STRING = 1,
	PIPE = 2,
	DOLLAR_SIGN = 3,
	SINGLE_QUOTE = 4,
	DOUBLE_QUOTE = 5,
	APPEND = 6,
	HERE_DOC = 7,
	REDIRECT_OUTPUT = 8,
	REDIRECT_INPUT = 9,
}	t_type;

typedef struct s_token
{
	char	*token;
	t_type	type;
	char	inquote;
	int		cmd_n;
}	t_token;

typedef struct s_minishell
{
	char				*arg;
	char				*path;
	char				**envp;
	int					envpset;
	int					token_count;
	struct s_token		*token;
	struct sigaction	sigact;
	struct s_cmd		*s_cmd;
	unsigned char		exit_code;
	char				*heredoc_flag;
	int					heredoc_count;
	int					prev_heredoc;
	int					count;
	int					cmd_n;
	int					sigint;
}	t_minishell;

t_minishell *minishell(t_minishell *mini);
int		isbuildin(char *isbuildin);
int		execute_buildin(t_minishell *mini);
int		here_doc(t_minishell *mini, char *delimiter);
int		set_heredoc_flag(t_minishell *mini);
char	*heredoc_substitution(t_minishell *mini, char *new_line);
void	count_heredoc(t_minishell *mini);
void	initialize_s_cmd(t_minishell *mini);
char	*heredoc_extra(t_minishell *mini, char *new, int *i, char *new_line);
char	*heredoc_sub(t_minishell *mini, char *new, int *i, char *new_line);

//utils_exec.c
//parsing
void	read_input(t_minishell *mini);
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
int		message_perror(char *str);
int		count_2darray(char **table);
int		whitespace_check(char *str);
void	set_signal_for_process(t_minishell *mini);
void	set_signal_for_heredoc(t_minishell *mini);
void	signal_reset(t_minishell *mini);
//void	print_tokens(t_token *tokens, int token_count);

// buildins and start of exec
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
int		ft_exit(t_minishell *mini);
void	print_env(t_minishell *mini);
int		ft_atoll(const char *str);

//new functions Valerie
void	nb_of_arg(t_minishell *mini, int n);
void	cpy_cmd(t_minishell *mini, int n, int i);
void	find_cmd(t_minishell *mini, int n);
void	null_command2(t_minishell *mini, int n);
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
void	child_path(t_minishell *mini);
char	*child_path_execve(char *string);
char	**child_array_execve(char **array);
void	child_closenfree(t_minishell *mini);
void	execve_failed(char *path_execve, char **array_execve);
void	child2(t_minishell *mini, int n);
int		parent2(t_minishell *mini);
void	exec_bash_cmd(t_minishell *mini, int n);
int		forker2(t_minishell *mini);
void	time_to_execute(t_minishell *mini);
char	*free_n_null(char *array);

//tokenize and new parsing
t_token	*tokenize(t_minishell *mini, char *arg);
int		get_tokens(t_minishell *mini, t_token *tokens, char *arg);
int		count_tokens(t_minishell *mini, char *arg);
int		new_substitution(t_minishell *mini, t_token *tokens, char *arg, int *i);
char	*get_exit_code(t_minishell *mini);
t_type	get_type(char *arg);
int		redir_parsing2(t_minishell *mini);
void	find_cmd(t_minishell *mini, int n);
int		pipe_parsing(t_minishell *mini, char *arg);
void	manual_redirection_loop(t_minishell *mini, int n, int i);
void	manual_redirection(t_minishell *mini, int n);
int		do_substitution(t_minishell *mini, t_token *tokens, char *arg, int *i);
int		get_token_str_loop(t_minishell *mini, \
		t_token *tokens, char *arg, int *i);
int		count_string_loop(char *arg, int *i, t_type type, t_type quote_type);
void	print_tokens(t_token *tokens, int token_count); // remove this
void	set_flag(t_minishell *mini, t_token tokens);

#endif