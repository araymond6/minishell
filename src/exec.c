#include "../include/minishell.h"
// check if it<s a build0in or not and execute it
int execute_cmd_buildin(t_minishell *mini)
{
    int exit_code;
    if(strlen(mini->s_cmd->cmd_arg[0]) == 0)
        exit(0);
    if (isbuildin(mini->s_cmd->cmd_arg[0]) == 0)
    {
        exit_code = execute_buildin(mini);
        exit(exit_code);
    }
    else
    {
        if (execve(mini->s_cmd->path, mini->s_cmd->cmd_arg, NULL) == -1)
        {
            free_scmd(mini->s_cmd);
            return (message_perror("EXECVE"));
        }
    }
    return (0);
}
// parent side of the process
int parent(t_cmd *cmd)
{
    int originalstdin;
    originalstdin = dup(STDIN_FILENO);
    close(cmd->fd[1]);
    if (cmd->prev->cmd != NULL)
    {
        if (dup2(cmd->prev->fd[0], STDIN_FILENO) == -1)
        {
            close(cmd->fd[0]);
            exit(EXIT_FAILURE);
        }
    }
    if (cmd->prev->cmd != NULL)
        close(cmd->prev->fd[0]);
    if (cmd->next->cmd == NULL)
        close(cmd->fd[0]);
    if (dup2(originalstdin, STDIN_FILENO) == -1)
        return (message_perror("Error restoring stdin"));
    return (0);
}
// child side of the process - make the execution
int child(t_minishell *mini)
{
    int i;
    i = -1;
    if (mini->s_cmd->prev->cmd != NULL)
        if (dup2(mini->s_cmd->prev->fd[0], STDIN_FILENO) == -1)
            return (close(mini->s_cmd->fd[0]), \
                close(mini->s_cmd->fd[1]), EXIT_FAILURE);
    if (mini->s_cmd->next->cmd != NULL && mini->s_cmd->next)
        if (dup2(mini->s_cmd->fd[1], STDOUT_FILENO) == -1)
            return (close(mini->s_cmd->fd[0]), \
                close(mini->s_cmd->fd[1]), EXIT_FAILURE);
    if (mini->s_cmd->prev->cmd != NULL)
        close(mini->s_cmd->prev->fd[0]);
    if (mini->s_cmd->next->cmd == NULL)
        close(mini->s_cmd->fd[0]);
    close(mini->s_cmd->fd[1]);
    if (mini->s_cmd->redir)
    {
        while (mini->s_cmd->redir[++i])
        {
            change_inf(mini->s_cmd->redir[i], mini->s_cmd->file[i]);
            change_out(mini->s_cmd->redir[i], mini->s_cmd->file[i]);
        }
    }
    return (execute_cmd_buildin(mini));
}
/*int to_fork()
{
    pids[i] = fork();
    if (pids[i] < 0)
        return (free_scmd(mini->s_cmd), message_perror("Fork"));
    else if (pids[i] == 0)
    {
        child(mini);
        mini->s_cmd = mini->s_cmd->next;
    }
    else if (pids[i] > 0)
    {
        parent(mini->s_cmd);
        mini->s_cmd = mini->s_cmd->next;
        forker(n - 1, pids +1, mini);
    }
}*/
int forker(int n, int *pids, t_minishell *mini)
{
    int i;
    i = 0;
    if (pipe(mini->s_cmd->fd) == -1)
        return (free_scmd(mini->s_cmd), message_perror("Pipe"));
    if (n > 0)
    {
        if(mini->s_cmd->cmd == NULL)
        {
            parent(mini->s_cmd);
            mini->s_cmd = mini->s_cmd->next;
            forker(n - 1, pids +1, mini);
        }
        else if(isbuildin(mini->s_cmd->cmd) == 0)
        {
            execute_buildin(mini);
            parent(mini->s_cmd);
            mini->s_cmd = mini->s_cmd->next;
            forker(n - 1, pids +1, mini);
        }
        else
        {
            pids[i] = fork();
            if (pids[i] < 0)
                return (free_scmd(mini->s_cmd), message_perror("Fork"));
            else if (pids[i] == 0)
            {
                child(mini);
                mini->s_cmd = mini->s_cmd->next;
            }
            else if (pids[i] > 0)
            {
                parent(mini->s_cmd);
                mini->s_cmd = mini->s_cmd->next;
                forker(n - 1, pids +1, mini);
            }
        }
    }
    return (0);
}
void all_here_doc(t_minishell *mini, int n)
{
    int f;
    t_cmd   *cmd2;
    f = 0;
    cmd2 = mini->s_cmd;
    while(cmd2->cmd)
    {
        if(cmd2->file)
        {
            while(cmd2->file[f])
            {
                if(cmd2->redir[f] == '2')
                    here_doc(cmd2->file[f]);
                f++;
            }
        }
        f = 0;
        cmd2 = cmd2->next;
    }
}
// the processus
int process(t_minishell *mini)
{
    pid_t   *pids;
    int     i;
    int     n;
    n = 0;
    i = 0;
    while (mini->cmd[n])
        n++;
    all_here_doc(mini, n);
    pids = ft_calloc(n, sizeof(pid_t));
    pids[i] = 1;
    while (mini->s_cmd->next)
        forker(n, pids, mini);
    i = 0;
    while (i < n)
    {       waitpid(pids[i], &mini->s_cmd->status, 0);
        if (WEXITSTATUS(mini->s_cmd->status) == 1)
            message_perror("WEXITSTATUS");
        i++;
    }
    return (0);
}
