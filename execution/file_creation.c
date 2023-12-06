/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:05:22 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/16 22:26:41 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirections(t_cmd	*cmd, t_minishell	*mini)
{
	file_creation(cmd, mini);
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

void	file_creation(t_cmd	*cmd, t_minishell	*mini)
{
	int	j;

	j = 0;
	(void)mini;
	while (cmd->files[j])
	{
		if (check_ambig(cmd->files[j], mini) == 1)
			exit(1);
		if (cmd->files[j][0] == '>' && cmd->files[j][1] == '>')
			append_files(cmd, j);
		else if (cmd->files[j][0] == '>')
			out_redirection_files(cmd, j);
		else if (cmd->files[j][0] == '<')
			in_redirection_files(cmd, j);
		j++;
	}
}

void	append_files(t_cmd	*cmd, int j)
{
	cmd->fd_out = (open(ft_substr(cmd->files[j], 2, ft_strlen(\
	cmd->files[j])), O_RDWR | O_CREAT | O_APPEND, 0660));
	if (cmd->fd_out == -1)
	{
		if (access(ft_substr(cmd->files[j], 2, ft_strlen(\
		cmd->files[j])), F_OK) != 0)
		{
			ft_putstr_fd("minishell: No such file or directory\n", 2);
			exit(1);
		}
		if (access(ft_substr(cmd->files[j], 2, ft_strlen(\
		cmd->files[j])), W_OK) != 0)
		{
			printf("minishell: %s: Permission denied\n", \
			ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])));
			exit(1);
		}
	}
}

void	out_redirection_files(t_cmd	*cmd, int j)
{
	cmd->fd_out = (open(ft_substr(cmd->files[j], 2, ft_strlen(\
	cmd->files[j])), O_RDWR | O_CREAT | O_TRUNC, 0660));
	if (cmd->fd_out == -1)
	{
		if (access(ft_substr(cmd->files[j], 2, ft_strlen(\
		cmd->files[j])), F_OK) != 0)
		{
			ft_putstr_fd("minishell: No such file or directory\n", 2);
			exit(1);
		}
		if (access(ft_substr(cmd->files[j], 2, ft_strlen(\
		cmd->files[j])), W_OK) != 0)
		{
			printf("minishell: %s: Permission denied\n", \
			ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])));
			exit(1);
		}
	}
}

void	in_redirection_files(t_cmd	*cmd, int j)
{
	if (access(ft_substr(cmd->files[j], 2, ft_strlen(\
	cmd->files[j])), F_OK) != 0)
	{
		cmd->general_info->in_file_exist = 1;
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		exit(1);
	}
	if (access(ft_substr(cmd->files[j], 2, ft_strlen(\
	cmd->files[j])), W_OK) != 0)
	{
		cmd->general_info->in_file_exist = 1;
		printf("minishell: %s: Permission denied\n", \
		ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])));
		exit(1);
	}
	cmd->fd_in = open(ft_substr(cmd->files[j], 2, \
	ft_strlen(cmd->files[j])), O_RDONLY);
}
