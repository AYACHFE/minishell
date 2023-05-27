/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:50:59 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/27 20:23:14 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_1(t_minishell	*mini, t_cmd	*cmd, char	**env)
{
	int	i;
	int	fd[2];
	// int	fd_2[2];
	int	pid;

	i = 0;
	(void)cmd;
	(void)mini;
	(void)env;
	if (cmd->general_info->cmd_nb == 1){
		built_in_cmd_fork(mini, &cmd[i], env);
		return ;
	}
	// while (i < cmd->general_info->cmd_nb)
	// {
		if (pipe(fd) == -1)
			exit(0);
		// if (pipe(fd_2) == -1)
		// 	exit(0);
			// last_read = fd[0];
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
			// close(0);
			
			built_in_cmd_2(mini, &cmd[i], env);
			exit(0);
		}
		i++;
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[0], 0);
			close(fd[0]);
			// close(fd[0]);
			close(fd[1]);
			// close(1);
			built_in_cmd_2(mini, &cmd[i], env);
			// puts("\n\nhere--->\n\n");
		}
		// else
		// 	wait(NULL);
	// 	i++;
	// }
}
