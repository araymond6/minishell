/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:33:20 by araymond          #+#    #+#             */
/*   Updated: 2023/08/04 15:57:40 by vst-pier         ###   ########.fr       */
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
	char			**file;	//tableaux de redirection d'entrée et sortie?
	struct s_cmd	*next; // le prochain block
	char			**delimiter; //tableaux de redirection here_doc ?
	int				nb_redir; 
}	t_cmd;

typedef struct s_minishell // ce que je vais recevoir en parametre
{
	char			*path_envp;
	char			*arg;	// pas important
	char			**cmd;  //tableaux des commandes par bloc
	struct s_cmd	*struct_cmd;
}	t_minishell;

//parsing
int	read_input(t_minishell *mini);

void	save_path(t_minishell *mini, char **envp);
//execution

#endif