/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:00:47 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/18 21:20:58 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	here_doc(t_cmd	*cmd, t_minishell	*mini)
{
	int		fd[2];
	int		i;
	int		j;
	t_prep	prep;

	i = 0;
	j = 0;
	prep.j = 0;
	while (cmd->eof[prep.j])
	{
		if (pipe(fd) == -1)
			exit(0);
		if (here_doc_ext(cmd, mini, &prep, fd) == -1)
			return (-1);
		close (fd[1]);
		cmd->fd_in = dup(fd[0]);
		close (fd[0]);
	}
	return (0);
}

int	here_doc_ext_3(char	*read, t_minishell	*mini, t_cmd	*cmd, t_prep	*prep)
{
	(void)mini;
	// if (!read)
	// {
	// 	if (rl_catch_signals)
	// 	{
	// 		mini->exit_code = 1;
	// 		return (-1);
	// 	}
	// }
	if (here_doc_ext_2(read, cmd, prep) == 1)
		return (1);
	return (0);
}

void	here_doc_checker(char	*read, int check, int	*fd, char	**res)
{
	if (check == 0)
		ft_putendl_fd(read, fd[1]);
	else
		here_doc_ext_1(res, read, fd);
	free(read);
}

int	here_doc_ext(t_cmd	*cmd, t_minishell	*mini, t_prep	*prep, int	*fd)
{
	char	*read;
	char	**res;
	int		check;
	int		ret;
	int		i;

	i = 0;
	check = 0;
	res = NULL;
	while (1)
	{
		read = readline("> ");
		ret = here_doc_ext_3(read, mini, cmd, prep);
		if (ret == -1)
			return (-1);
		if (ret == 1)
			break ;
		if ((ft_strchr(read, '$') != 0) && mini->do_not_exp == 0)
		{
			res = malloc(sizeof(char *) * (count(read, 32) + 1));
			check = 1;
			ft_check_dollar_heredoc(mini, read, res);
		}
		here_doc_checker(read, check, fd, res);
	}
	return (0);
}

void	here_doc_ext_1(char	**res, char	*read, int	*fd)
{
	int	i;

	i = 0;
	while (i < count(read, 32))
	{
		ft_putstr_fd(res[i++], fd[1]);
		ft_putchar_fd(32, fd[1]);
	}
	ft_putchar_fd('\n', fd[1]);
}

int	here_doc_ext_2(char	*read, t_cmd	*cmd, t_prep	*prep)
{
	if (read == NULL || (ft_strncmp(read, cmd->eof[prep->j], \
	ft_strlen(read) + 1) == 0))
	{
		prep->j++;
		free(read);
		return (1);
	}
	return (0);
}
