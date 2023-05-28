/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:50:59 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/28 14:21:19 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_1(t_minishell	*mini, t_cmd	*cmd, char	**env)
{
	int	i;
	int	fd[2];
	int	pid;
	int	stdi;

	i = 0;
	(void)cmd;
	(void)mini;
	(void)env;
	stdi = dup(0);
	while (i < cmd->general_info->cmd_nb - 1)
	{
		if (pipe(fd) == -1)
			exit(0);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
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
		
		close(fd[0]);
		close(fd[1]);
		built_in_cmd_2(mini, &cmd[i], env);
		exit(0);
	}
	dup2(stdi, 0);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	while (wait(NULL) > 0) ;
}
