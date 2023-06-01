/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:50:59 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/01 12:05:42 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		printf("cmd->eof[j] == '%s'\n", cmd->eof[j]);
		while (1)
		{
			read = readline("> ");
			// printf("");
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
		// dup2(fd[0], 0);
		// close(cmd->fd_in);
		close (fd[0]);
	}
}

void	file_creation(t_cmd	*cmd)
{
	int	i;

	i = 0;
	while (i < cmd->general_info->files_nb)
	{
		// printf("file == '%s'\n",cmd->general_info->files[i]);
		if (cmd->general_info->files[i][0] == '>' && cmd->general_info->files[i][1] == '>')
		{
			//append >>
			cmd->fd_out = (open(ft_substr(cmd->general_info->files[i], 2, ft_strlen(cmd->general_info->files[i])), O_RDWR | O_CREAT | O_APPEND, 0660));
			if (cmd[i].fd_out == -1)
			{
				perror("open");
				return ;
			}
		}
		else if (cmd->general_info->files[i][0] == '>')
		{
			//out_redirection
			cmd->fd_out = (open(ft_substr(cmd->general_info->files[i], 2, ft_strlen(cmd->general_info->files[i])), O_RDWR | O_CREAT | O_TRUNC, 0660));
			if (cmd[i].fd_out == -1)
			{
				perror("open");
				return ;
			}
		}
		else if (cmd->general_info->files[i][0] == '<')
		{
			//in_redirection
			if (access(ft_substr(cmd->general_info->files[i], 2, ft_strlen(cmd->general_info->files[i])), F_OK) != 0)
			{
				perror(cmd->general_info->files[i]);
				break ;
			}
			cmd[i].fd_in = open(ft_substr(cmd->general_info->files[i], 2, ft_strlen(cmd->general_info->files[i])), O_RDONLY);
		}
		i++;
	}
}

void	redirections(t_cmd	*cmd)
{
	// printf("cmd->args[0] == %s\n", cmd->args[0]);
	// printf("cmd->general_info->here_doc_nb == %d\n", cmd->general_info->here_doc_nb);
	// if (cmd->here_doc == 1)
	// if (cmd->general_info->here_doc_nb > 0)
	// {
	// 	here_doc(cmd);
	// 	dup2(cmd->fd_in, 0);
	// 	close(cmd->fd_in);
	// }
	file_creation(cmd);
	if (cmd->in_red == 1)
	{
		// puts("-----_>");
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
		if (cmd->here_doc == 1)
		{
			puts("--->");
			here_doc(cmd);
			dup2(cmd->fd_in, 0);
			close(cmd->fd_in);
		}
		if (pipe(fd) == -1)
			exit(0);
		pid = fork();
		if (pid == 0)
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
	if (cmd->here_doc == 1)
	{
		puts("------------2222------------");
		here_doc(cmd);
		dup2(cmd->fd_in, 0);
		close(cmd->fd_in);
	}
	if (pipe(fd) == -1)
		exit(0);
	pid = fork();
	if (pid == 0)
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
	waitpid(pid, NULL, 0);
	while (wait(NULL) > 0) ;
}
