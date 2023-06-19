/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:50:59 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/19 12:00:27 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_code(t_prep	*prep, t_cmd	*cmd, t_minishell	*mini)
{
	int	status;

	prep->i = 0;
	while (prep->i < cmd->general_info->cmd_nb)
		waitpid(prep->pid[prep->i++], &status, 0);
	if (status == 2)
		mini->exit_code = 130;
	else
		mini->exit_code = status >> 8;
}

int	exec_1_ext(t_cmd	*cmd, t_minishell	*mini, t_prep	*prep, char	**env)
{
	int	checker;

	while (prep->i < cmd->general_info->cmd_nb - 1)
	{
		if (multi_cmd(cmd, mini, prep, env) == -1)
		{
			free(prep->pid);
			free(prep);
			return (1);
		}
		dup2(prep->fd[0], 0);
		close(prep->fd[1]);
		close(prep->fd[0]);
		prep->i++;
	}
	checker = single_cmd(cmd, mini, prep, env);
	if (checker == 1 || checker == -1)
	{
		free(prep->pid);
		free(prep);
		return (1);
	}
	return (0);
}

void	exec_1(t_minishell	*mini, t_cmd	*cmd, char	**env)
{
	t_prep	*prep;

	cmd->general_info->std_in = dup(0);
	cmd->general_info->std_out = dup(1);
	prep = malloc(sizeof(t_prep));
	prep->i = 0;
	prep->pid = malloc(sizeof(int *) * (cmd->general_info->cmd_nb + 2));
	if (exec_1_ext(cmd, mini, prep, env) == 1)
		return ;
	dup2(cmd->general_info->std_in, 0);
	dup2(cmd->general_info->std_out, 1);
	close(prep->fd[0]);
	close(prep->fd[1]);
	exit_code(prep, cmd, mini);
	free(prep->pid);
	free(prep);
}

int	multi_cmd(t_cmd	*cmd, t_minishell	*mini, t_prep	*prep, char	**env)
{
	if (cmd[prep->i].args[0] && built_in_cmd_3(mini, &cmd[prep->i]))
	{
		prep->i++;
		return (0);
	}
	if (cmd[prep->i].here_doc == 1)
	{
		if (mutli_cmd_ext(cmd, prep, mini) == -1)
			return (-1);
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
	return (0);
}

int	single_cmd(t_cmd	*cmd, t_minishell	*mini, t_prep	*prep, char	**env)
{
	if (cmd[prep->i].here_doc == 1)
	{
		dup2(cmd->general_info->std_in, 0);
		dup2(cmd->general_info->std_out, 1);
		if (here_doc(&cmd[prep->i], mini) == -1)
			return (-1);
		dup2(cmd[prep->i].fd_in, 0);
		close(cmd[prep->i].fd_in);
	}
	if (cmd[prep->i].args[0] && built_in_cmd_3(mini, &cmd[prep->i]))
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
