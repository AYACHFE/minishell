/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:50:59 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/16 21:54:48 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	multi_cmd(t_cmd	*cmd, t_minishell	*mini, t_prep	*prep, char	**env)
{
	if (cmd[prep->i].args[0] && built_in_cmd_3(mini, &cmd[prep->i], env))
	{
		prep->i++;
		return ;
	}
	if (cmd[prep->i].here_doc == 1)
	{
		dup2(cmd->general_info->std_in, 0);
		dup2(cmd->general_info->std_out, 1);
		here_doc(&cmd[prep->i], mini);
		dup2(cmd[prep->i].fd_in, 0);
		close(cmd[prep->i].fd_in);
	}
	if (pipe(prep->fd) == -1)
		exit(0);
	prep->pid[prep->i] = fork();
	if (prep->pid[prep->i] == 0)
	{
		dup2(prep->fd[1], 1);
		close(prep->fd[1]);
		close(prep->fd[0]);
		redirections(&cmd[prep->i], mini);
		built_in_cmd_2(mini, &cmd[prep->i], env);
		exit(0);
	}
}

int	single_cmd(t_cmd	*cmd, t_minishell	*mini, t_prep	*prep, char	**env)
{
	if (cmd[prep->i].here_doc == 1)
	{
		dup2(cmd->general_info->std_in, 0);
		dup2(cmd->general_info->std_out, 1);
		here_doc(&cmd[prep->i], mini);
		dup2(cmd[prep->i].fd_in, 0);
		close(cmd[prep->i].fd_in);
	}
	if (cmd[prep->i].args[0] && built_in_cmd_3(mini, &cmd[prep->i], env))
		return (1);
	if (pipe(prep->fd) == -1)
		exit(0);
	prep->pid[prep->i] = fork();
	if (prep->pid[prep->i] == 0)
	{
		close(prep->fd[0]);
		close(prep->fd[1]);
		redirections(&cmd[prep->i], mini);
		built_in_cmd_2(mini, &cmd[prep->i], env);
		exit(0);
	}
	return (0);
}

void	exec_1(t_minishell	*mini, t_cmd	*cmd, char	**env)
{
	t_prep	prep;
	int 	status;

	cmd->general_info->std_in = dup(0);
	cmd->general_info->std_out = dup(1);
	prep.i = 0;
	prep.pid = malloc(sizeof(int) * cmd->general_info->cmd_nb);
	while (prep.i < cmd->general_info->cmd_nb - 1)
	{
		multi_cmd(cmd, mini, &prep, env);
		dup2(prep.fd[0], 0);
		close(prep.fd[1]);
		close(prep.fd[0]);
		prep.i++;
	}
	if (single_cmd(cmd, mini, &prep, env) == 1)
		return ;
	dup2(cmd->general_info->std_in, 0);
	dup2(cmd->general_info->std_out, 1);
	close(prep.fd[0]);
	close(prep.fd[1]);
	prep.i = 0;
	while(prep.i < cmd->general_info->cmd_nb)
		waitpid(prep.pid[prep.i++], &status, 0);
	mini->exit_code = WEXITSTATUS(status);
}
