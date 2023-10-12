#include "../include/minishell.h"

//TODO prend un long long

//TODO exit | exit ne ferme pas voir bash. Ne ferme que les pipe

//TODO quand le premier argument est valide et un des autres non il ferme pas voir bash 

//TODO quand il y a plus de 1 argument il ne ferme pas et dir trop d<argument exit 

void	free_scmd(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = cmd;
	while (temp)
	{
		if (temp->redir)
			free(temp->redir);
		if (temp->cmd)
			free(temp->cmd);
		if (temp->path)
			free(temp->path);
		if (temp->cmd_arg)
			free_array(temp->cmd_arg);
		if (cmd->file)
			free_array(temp->file);
		temp = temp->next;
		free(cmd);
		cmd = temp;
	}
}

void	ft_exit(t_minishell *mini)
{
	int	nb_arg;

	nb_arg = 0;
	while (mini->s_cmd->cmd_arg[nb_arg])
		nb_arg++;
	if (nb_arg == 1)
	{
		free_scmd(mini->s_cmd);
		exit_program(mini);
	}
	//non valide = pas chiffre (Prends chiffre negatif aussi)
	if (nb_arg == 2)
	{
		// un argument valide -> sort
		// un argument non valide -> ne sort pas
	}
	else if (nb_arg > 2)
	{
		// plusieurs argument avec le premier valide -> ne sort pas
		// plusieurs argument avec le premier invalide -> sort
	}
}
