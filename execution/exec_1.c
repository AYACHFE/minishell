/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:50:59 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/14 18:06:28 by aachfenn         ###   ########.fr       */
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
			here_doc(&cmd[i], mini);
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
			redirections(&cmd[i], mini);
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
		here_doc(&cmd[i], mini);
		dup2(cmd[i].fd_in, 0);
		close(cmd[i].fd_in);
	}
	//this part fixes "cd .. > out" but it drops the tester to 72%
	// int	no_fork = built_in_cmd_3_check(mini, &cmd[i], env);
	// if (cmd[i].args[0] && no_fork == 1)
	// {
	// 	if (cmd[i].files[0])
	// 		file_creation(&cmd[i], mini);
	// 	built_in_cmd_3(mini, &cmd[i], env);
	// 	return ;
	// }
	if (cmd[i].args[0] && built_in_cmd_3(mini, &cmd[i], env))
		return ;
	if (pipe(fd) == -1)
		exit(0);
	pid[i] = fork();
	if (pid[i] == 0)
	{
		close(fd[0]);
		close(fd[1]);
		redirections(&cmd[i], mini);
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
}

void	execv_function(t_minishell	*mini, t_cmd	*cmd, char **env)
{
	(void)mini;
	int		i;
	int		j;
	int		path_nb;
	char	**var = NULL;
	char	*val;


	i = 0;
	j = 0;
	//new
	path_nb = 1;
	(void)env;
	if (cmd->general_info->in_file_exist == 1)
		exit(1);
	if (cmd->args[0][0] != '/')
	{
		while (mini->my_env[i] != NULL)
		{
			if (ft_strncmp(mini->my_env[i], "PATH", 4) == 0)
			{
				var = ft_split(ft_substr(mini->my_env[i], 5, ft_strlen(mini->my_env[i])), ':');
				break ;
			}
			if (mini->my_env[i + 1] == NULL)
			{
				printf("minishell: No such file or directory\n");
				exit(127);
			}
			i++;
		}
		path_nb = count(ft_substr(mini->my_env[i], 5, ft_strlen(mini->my_env[i])), ':');
		while (j < path_nb)
		{
			val = ft_strjoin(var[j], "/");
			val = ft_strjoin(val, cmd->args[0]);
			if (access(val, F_OK) == 0)
			{
				// free(var[j]);
				// free(var);
				execve(val, cmd->args, mini->my_env);
			}
			free(var[j]);
			free(val);
			j++;
		}
	}
	else 
	{
		// puts("----->");
		if (access(cmd->args[0], F_OK) == 0)
		{
			execve(cmd->args[0], cmd->args, mini->my_env);
		}
	}
	mini->exit_code = 1;
	// if (cmd->args[1][0] == '/')
	if (cmd->args[0][0] == '/')
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
	}
	else
	{
		char *str = ft_strjoin("minishell: ", cmd->args[0]);
		char *str1 = ft_strjoin(str, ": command not found\n");
		ft_putstr_fd(str1, 2);
		free(str);
		free(str1);
	}
	free(var);
	mini->exit_code = 127;
	exit(127);
}

void	here_doc(t_cmd	*cmd, t_minishell	*mini)
{
	char	*read;
	int		fd[2];
	int		i;
	int		j;
	int		rd;
	char	**res;
	int		check;

	check = 0;
	i = 0;
	j = 0;
	(void)mini;
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
				free(read);
				break ;
			}
			if ((ft_strchr(read, '$') != 0) && mini->do_not_exp == 0)
			{
				res = malloc(sizeof(char *) * (count(read, 32) + 1));
				check = 1;
				ft_check_dollar_heredoc(mini, read, res);
			}
			if (check == 0)
			{
				ft_putstr_fd(read, fd[1]);
				ft_putchar_fd('\n', fd[1]);
			}
			else
			{
				i = 0;
				while (i < count(read, 32))
				{
					ft_putstr_fd(res[i++], fd[1]);
					ft_putchar_fd(32, fd[1]);
				}
				ft_putchar_fd('\n', fd[1]);
			}
			free(read);
		}
		close (fd[1]);
		rd = dup(fd[0]);
		cmd->fd_in = rd;
		close (fd[0]);
	}
}

int	check_ambig(char	*file, t_minishell	*mini)
{
	int	i;
	int	j;
	
	i = 0;
	j = 2;
	(void)cmd;
	// printf("file '%s'\n", file);
	// printf("center_sp %d\n", mini->center_sp);
	// printf("right_sp %d\n", mini->right_sp);
	// printf("left_sp %d\n", mini->left_sp);
	// printf("just_sp %d\n", mini->just_sp);
	if (mini->center_sp == 1 || mini->just_sp == 1)
	{
		// puts("center");
		ft_putendl_fd("minishell: ambiguous redirect", 2);
		return (1);
	}
	if (mini->left_sp == 1)
	{
		while (file[j])
		{
			if (file[j] == 32 && (file[j - 1] != 32 && file[j - 1] != '>' && file[j - 2] != '>'))
			{
				// printf("'%d'----'%c'\n", j, file[j]);
				ft_putendl_fd("minishell: ambiguous redirect", 2);
				return (1);
			}
			j++;
		}
	}
	j = 2;
	if (mini->right_sp == 1)
	{
		while (file[j])
		{
			if (file[j] == 32 && (file[j + 1] != '\0'))
			{
				ft_putendl_fd("minishell: ambiguous redirect", 2);
				return (1);
			}
			j++;
		}
	}
	return (0);
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
		{
			//append >>
			cmd->fd_out = (open(ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])), O_RDWR | O_CREAT | O_APPEND, 0660));
			if (cmd->fd_out == -1)
			{
				if (access(ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])), F_OK) != 0)
				{
					ft_putstr_fd("minishell: No such file or directory\n", 2);
					exit(1);
				}
				if (access(ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])), W_OK) != 0)
				{
					printf("minishell: %s: Permission denied\n", ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])));
					exit(1);
				}
			}
		}
		else if (cmd->files[j][0] == '>')
		{
			//out_redirection
			cmd->fd_out = (open(ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])), O_RDWR | O_CREAT | O_TRUNC, 0660));
			if (cmd->fd_out == -1)
			{
				if (access(ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])), F_OK) != 0)
				{
					ft_putstr_fd("minishell: No such file or directory\n", 2);
					exit(1);
				}
				if (access(ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])), W_OK) != 0)
				{
					printf("minishell: %s: Permission denied\n", ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])));
					exit(1);
				}
			}
		}
		else if (cmd->files[j][0] == '<')
		{
			//in_redirection
			if (access(ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])), F_OK) != 0)
			{
				cmd->general_info->in_file_exist = 1;
				ft_putstr_fd("minishell: No such file or directory\n", 2);
				exit(1);
			}
			if (access(ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])), W_OK) != 0)
			{
				cmd->general_info->in_file_exist = 1;
				printf("minishell: %s: Permission denied\n", ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])));
				exit(1);
			}
			cmd->fd_in = open(ft_substr(cmd->files[j], 2, ft_strlen(cmd->files[j])), O_RDONLY);
		}
		j++;
	}
}

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
