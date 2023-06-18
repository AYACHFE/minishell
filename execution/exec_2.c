/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:30:08 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/18 10:22:50 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_programs(t_cmd	*cmd, t_minishell	*mini)
{
	if (access(ft_substr(cmd->args[0], 2, ft_strlen(\
	cmd->args[0])), F_OK) == 0)
		execve(ft_substr(cmd->args[0], 2, ft_strlen(\
		cmd->args[0])), cmd->args, mini->my_env);
}

void	execv_function(t_minishell	*mini, t_cmd	*cmd)
{
	int		i;
	int		j;
	char	**var;

	i = 0;
	j = 0;
	var = NULL;
	if (cmd->general_info->in_file_exist == 1)
		exit(1);
	if (cmd->args[0][0] == '.' && cmd->args[0][1] == '/')
		execute_programs(cmd, mini);
	if (cmd->args[0][0] != '/')
	{
		if (mini->my_env[0] == NULL)
			execve_error(mini, cmd);
		execve_func_ext(mini, cmd);
	}
	else
	{
		if (access(cmd->args[0], F_OK) == 0)
			execve(cmd->args[0], cmd->args, mini->my_env);
	}
	free(var);
	execve_error(mini, cmd);
}

void	execve_func_ext(t_minishell	*mini, t_cmd	*cmd)
{
	char	**var;
	int		j;
	int		i;

	j = 0;
	i = 0;
	var = NULL;
	while (mini->my_env[i] != NULL)
	{
		if (ft_strncmp(mini->my_env[i], "PATH", 4) == 0)
		{
			var = ft_split(ft_substr(mini->my_env[i], 5, \
			ft_strlen(mini->my_env[i])), ':');
			break ;
		}
		if (mini->my_env[i + 1] == NULL)
		{
			ft_putendl_fd("minishell: No such file or directory", 2);
			exit(127);
		}
		i++;
	}
	execve_func_ext_1(mini, cmd, i, var);
}

void	execve_func_ext_1(t_minishell	*mini, t_cmd	\
*cmd, int i, char	**var)
{
	char	*val;
	int		path_nb;
	int		j;

	j = 0;
	path_nb = count(ft_substr(mini->my_env[i], 5, ft_strlen(\
	mini->my_env[i])), ':');
	while (j < path_nb)
	{
		val = ft_strjoin(var[j], "/");
		val = ft_strjoin(val, cmd->args[0]);
		if (access(val, F_OK) == 0)
			execve(val, cmd->args, mini->my_env);
		free(var[j]);
		free(val);
		j++;
	}
}

void	execve_error(t_minishell	*mini, t_cmd	*cmd)
{
	char	*str;
	char	*str1;

	mini->exit_code = 1;
	if ((cmd->args[0][0] == '/' && cmd->args[0][1] == 'b' && \
	cmd->args[0][2] == 'i' && cmd->args[0][3] == 'n') && (\
	cmd->args[0][4] == '\0'))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": is a directory", 2);
	}
	else if (cmd->args[0][0] == '/')
		ft_putstr_fd("minishell: No such file or directory\n", 2);
	else
	{
		str = ft_strjoin("minishell: ", cmd->args[0]);
		str1 = ft_strjoin(str, ": command not found\n");
		ft_putstr_fd(str1, 2);
		free(str);
		free(str1);
	}
	mini->exit_code = 127;
	exit(127);
}
