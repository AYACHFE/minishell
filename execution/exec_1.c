/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:50:59 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/18 18:16:08 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_code(t_prep	*prep, t_cmd	*cmd, t_minishell	*mini)
{
	int	status;
	// unsigned char *str;

	prep->i = 0;
	while (prep->i < cmd->general_info->cmd_nb)
		waitpid(prep->pid[prep->i++], &status, 0);
	mini->exit_code = WEXITSTATUS(status);
}

void	exec_1(t_minishell	*mini, t_cmd	*cmd, char	**env)
{
	t_prep	*prep;
	int		checker;

	cmd->general_info->std_in = dup(0);
	cmd->general_info->std_out = dup(1);
	prep = malloc(sizeof(t_prep));
	prep->i = 0;
	prep->pid = malloc(sizeof(int *) * (cmd->general_info->cmd_nb + 2));
	while (prep->i < cmd->general_info->cmd_nb - 1)
	{
		if (multi_cmd(cmd, mini, prep, env) == -1)
		{
			free(prep->pid);
			free(prep);
			return ;
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
		return ;
	}
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
		dup2(cmd->general_info->std_in, 0);
		dup2(cmd->general_info->std_out, 1);
		if (here_doc(&cmd[prep->i], mini) == -1)
			return (-1);
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
