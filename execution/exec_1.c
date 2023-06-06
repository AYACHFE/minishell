/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:50:59 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/06 15:25:55 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_1(t_minishell	*mini, t_cmd	*cmd, char	**env)
{
	int	i;
	int	fd[2];
	int	pid[cmd->general_info->cmd_nb];
	int	stdi;
	int	stdou;
	int status;

	i = 0;
	(void)cmd;
	(void)mini;
	(void)env;
	stdi = dup(0);
	stdou = dup(1);
	cmd->general_info->std_in = dup(0);
	cmd->general_info->std_out = dup(1);
	while (i < cmd->general_info->cmd_nb - 1)
	{
		if (cmd[i].args[0] && built_in_cmd_3(mini, &cmd[i], env))
		{
			i++;
			return ;
		}
		if (cmd[i].here_doc == 1)
		{
			dup2(stdi, 0);
			dup2(stdou, 1);
			here_doc(&cmd[i]);
			dup2(cmd[i].fd_in, 0);
			close(cmd[i].fd_in);
		}
		if (pipe(fd) == -1)
			exit(0);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
			redirections(&cmd[i]);
			built_in_cmd_2(mini, &cmd[i], env);
			exit(0);
		}
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		i++;
	}
	/////////
	if (cmd[i].here_doc == 1)
	{
		dup2(stdi, 0);
		dup2(stdou, 1);
		here_doc(&cmd[i]);
		dup2(cmd[i].fd_in, 0);
		close(cmd[i].fd_in);
	}
	if (cmd[i].args[0] && built_in_cmd_3(mini, &cmd[i], env))
	{
		return ;
	}
	if (pipe(fd) == -1)
		exit(0);
	pid[i] = fork();
	if (pid[i] == 0)
	{
		close(fd[0]);
		close(fd[1]);
		redirections(&cmd[i]);
		built_in_cmd_2(mini, &cmd[i], env);
		exit(0);
	}
	dup2(stdi, 0);
	dup2(stdou, 1);
	close(fd[0]);
	close(fd[1]);
	i = 0;
	while(i < cmd->general_info->cmd_nb)
		waitpid(pid[i++], &status, 0);
	mini->exit_code = WEXITSTATUS(status);
	// printf("-->exit_code %d\n", mini->exit_code);
}

void	here_doc(t_cmd	*cmd)
{
	char	*read;
	int		fd[2];
	int		i;
	int		j;
	int		rd;

	i = 0;
	j = 0;
	while (cmd->eof[j])
	{
		if (pipe(fd) == -1)
			exit(0);
		// printf("cmd->eof[j] == '%s'\n", cmd->eof[j]);
		while (1)
		{
			read = readline("> ");
			if (ft_strncmp(read, cmd->eof[j], ft_strlen(read) + 1) == 0)
			{
				j++;
				break ;
			}
			ft_putstr_fd(read, fd[1]);
			ft_putchar_fd('\n', fd[1]);
		}
		close (fd[1]);
		rd = dup(fd[0]);
		cmd->fd_in = rd;
		close (fd[0]);
	}
}

void	file_creation(t_cmd	*cmd)
{
	int	j;

	j = 0;
	while (cmd->files[j])
	{
		if (cmd->files[j][0] == '>' && cmd->files[j][1] == '>')
		{
			//append >>
			cmd->fd_out = (open(ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])), O_RDWR | O_CREAT | O_APPEND, 0660));
			if (cmd->fd_out == -1)
			{
				printf("%d\n", access(ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])), W_OK));
				if (access(ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])), W_OK) != 0)
				{
					printf("minishell: %s: Permission denied\n", ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])));
					exit(1);
				}
				ft_putstr_fd("minishell: No such file or directory\n", 2);
				exit(1);
			}
		}
		else if (cmd->files[j][0] == '>')
		{
			//out_redirection
			cmd->fd_out = (open(ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])), O_RDWR | O_CREAT | O_TRUNC, 0660));
			if (cmd->fd_out == -1)
			{
				ft_putstr_fd("minishell: No such file or directory\n", 2);
				exit(1);
			}
		}
		else if (cmd->files[j][0] == '<')
		{
			//in_redirection
			// if (access(ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])), F_OK | X_OK) != 0)
			if (access(ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])), F_OK) != 0)
			{
				cmd->general_info->in_file_exist = 1;
				ft_putstr_fd("minishell: No such file or directory\n", 2);
				exit(1);
			}
			cmd->fd_in = open(ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])), O_RDONLY);
		}
		j++;
	}
}

void	redirections(t_cmd	*cmd)
{
	file_creation(cmd);
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
