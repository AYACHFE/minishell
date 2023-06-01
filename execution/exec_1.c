/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:50:59 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/01 15:10:19 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirections(t_cmd	*cmd)
{
	// if (cmd->here_doc == 1)
	// {
		
	// }
	if (cmd->in_red == 1)
	{
		dup2(cmd->fd_in, 0);
		close(cmd->fd_in);
	}
	if (cmd->append == 1)
	{
		dup2(cmd->fd_out, 1);
		close(cmd->fd_out);
	}
	else if (cmd->out_red == 1)
	{
		dup2(cmd->fd_out, 1);
		close(cmd->fd_out);
	}
}

void	exec_1(t_minishell	*mini, t_cmd	*cmd, char	**env)
{
	int	i;
	int	fd[2];
	int	pid;
	int	stdi;
	int	stdou;

	i = 0;
	(void)cmd;
	(void)mini;
	(void)env;
	stdi = dup(0);
	stdou = dup(1);
	while (i < cmd->general_info->cmd_nb - 1)
	{
		if (pipe(fd) == -1)
			exit(0);
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
			//redirections
			redirections(&cmd[i]);
			built_in_cmd_2(mini, &cmd[i], env);
			exit(0);
		}
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		i++;
	}
	if (pipe(fd) == -1)
		exit(0);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(fd[0]);
		close(fd[1]);
		//redirections
		redirections(&cmd[i]);
		built_in_cmd_2(mini, &cmd[i], env);
		exit(0);
	}
	dup2(stdi, 0);
	dup2(stdou, 1);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	while (wait(NULL) > 0) ;
}
