#include "../include/minishell.h"

/*if (parse(mini) == 0)
{
	---time_to_execute(mini)---
    if (create_list(mini) == 0)
		x_comm(mini);
}*/

//compter le nb de pipe
//faire les redirections de here_doc

int	nb_cmd(t_minishell *mini)
{
	int i;
	int nb_c;

	nb_c = 1;
	i = 0;
	while (i < mini->token_count)
	{
		if (mini->token[i].type == PIPE
			&& mini->token->indoublequote == 0
			&& mini->token->inquote == 0)
			nb_c++;
		i++;
	}
	return (nb_c);
}


char *file_name(t_minishell *mini, int i)
{
	int i2;
	int t;
	int f;
	int slen;
	char *file;

	i2 = i;
	slen = 0;
	t = 0;
	f = 0;
	if (mini->token->indoublequote == 1)
	{
		while (mini->token[i].indoublequote == 1) //////////////
		{
			slen += mini->token[i].len;
			i++;
		}
		file = ft_calloc(slen + 1, sizeof(char));
		while (mini->token[i2].indoublequote == 1) ///////////////
		{
			while (t < mini->token[i2].len)
			{
				file[f] = mini->token[i2].token[t];
				f++;
				t++;
			}
			t = 0;
		}
	}
	else if (mini->token->inquote == 1)
	{
		while (mini->token[i].inquote == 1)
		{
			slen += mini->token[i].len;
			i++;
		}
		file = ft_calloc(slen + 1, sizeof(char));
		while (mini->token[i2].inquote == 1)
		{
			while (t < mini->token[i2].len)
			{
				file[f] = mini->token[i2].token[t];
				f++;
				t++;
			}
			t = 0;
		}
	}
	else
	{
		if (mini->token[i].type == SPACE)
	}
	return (file);
}

void	all_here_doc2(t_minishell *mini)
{
	int	i;

	i = 0;
	while (i < mini->token_count)
	{
		if (mini->token[i].type == HERE_DOC
			&& mini->token->indoublequote == 0
			&& mini->token->inquote == 0)
		{
			//faire une fonction qui trouve le nom de fichier apres une redirection et le met dans une string
			//appeler la fonction here_doc apres et verifier si elle est encore bonne
			//here_doc(mini, cmd2->file[f]);
			here_doc(mini, file_name(mini, i + 1));
		}
		i++;
	}
}

int	time_to_execute(t_minishell *mini)
{
	int	nb_c;

	nb_c = nb_cmd(mini);
	all_here_doc2(mini);
}