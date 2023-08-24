/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerie <valerie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:20 by araymond          #+#    #+#             */
/*   Updated: 2023/08/24 11:38:39 by valerie          ###   ########.fr       */
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
	char			*redir;		//contient un tableaux de chiffre avec les redirections
	char			*cmd;		// contient la commande ex : ls -la
	char			*path;		// contient le path de la commande ex : /bin/ls
	char			**cmd_arg;	// le tableaux d<ont a besoin execve
	char			**file;		// tableaux de redirection d'entrée et sortie + Delimiter
	struct s_cmd	*next;		// le prochain block
	int				nb_redir;	// le nb de redirection au total
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_minishell		// ce que je vais recevoir en parametre
{
	char			*path_envp;
	char			*arg;		// pas important
	char			**cmd; 		//tableaux des commandes par bloc
	struct s_cmd	*struct_cmd;
}	t_minishell;

//parsing
int	read_input(t_minishell *mini);

void	save_path(t_minishell *mini, char **envp);
//execution




//function exec -> val

	//function qui malloc le tableaux des redirection redir, mais aussi le char **file qui va contenir le nom du fichier lie a la redirection
void	create_redir_file(t_minishell *mini);
	//function qui va mettre dans char *redir la sorte de redirection
void	assign_redir_values(t_minishell *mini, char c);
	//function qui va assigner les chose en cas de >> ou de >
int		entry_redirection(t_minishell *mini, int i, int j);
	//function qui va assigner les chose en cas de >> ou de >
int	exit_redirection(t_minishell *mini, int i, int j);
	//function qui va assigner les chose quand il trouve la commande
int		check_command(t_minishell *mini, int i, int j);
	//function qui va assigner les chose en cas de <
int		redirection1234(t_minishell *mini, int i, int j, char c);
	//function qui initilaize la struct cmd
void	initialize_struct_cmd(t_cmd *struct_cmd);
	//function qui compte le nb de caractere avant la prochaine espace
int		len_until_space(t_minishell *mini, int i, int j);
	//function qui compte le nb de redirection quil y aura
int		redir_count(char *cmd);
	//function qui parse la commande afin doute les commandes de mini dans la structure cmd
void	parsing_command(t_minishell *mini, int i);
int		len_until_redirections(t_minishell *mini, int i, int j);
void	free_array(char **array);
int 	ft_strjcpy(char *dst, char *src, int max, int j);
int		message_perror(char *str);
#endif