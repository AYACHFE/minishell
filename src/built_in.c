/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:45:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/05 19:39:13 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// the engine of this program
void	built_in_cmd(t_minishell	*mini, char **env)
{
	char	*str;
	t_cmd	*cmd = NULL;
	
	char	*s;
	char	*var;
	char	**ret;

	(void)mini;
	(void)env;
	str = readline("\033[0;34mMINISHELL-3.2$ \033[0m");
	if (!str)
		exit(mini->exit_code);
	add_history(str);
	//
	if (ft_error(str, 0) == 0)
	{
		mini->exit_code = 2;
		return ;
	}
	s = ft_strdup(str);
	var = prep(s);
	ret = ft_split(var, 11);
	//
	mini->cmd = ret;
	mini->cmd_nb = count(var, 11);
	//
	cmd = malloc(sizeof(t_cmd) * cmd_counter(mini));
	//

	mini->count_str = 0;
	if (ft_strlen(str) == 0)
		return ;
	ft_check_dollar(mini);
	mini->str = ft_split(str, ' ');
	mini->count_str = count(str, ' ');
	parcing(mini, cmd, str);
	exec_1(mini, cmd, env);
	
	// printf("exit_code %d\n", mini->exit_code);
	
	free(cmd);
	free(str);
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
	(void)env;
	// while (env[i] != NULL)
	// {
	// 	if (ft_strncmp(env[i], "PATH", 4) == 0)
	// 	{
	// 		var = ft_split(ft_substr(env[i], 5, ft_strlen(env[i])), ':');
	// 		break ;
	// 	}
	// 	i++;
	// }
	// path_nb = count(ft_substr(env[i], 5, ft_strlen(env[i])), ':');
	while (mini->my_env[i] != NULL)
	{
		// puts(mini->my_env[i]);
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
			free(var[j]);
			free(var);
			execve(val, cmd->args, mini->my_env);
		}
		free(var[j]);
		free(val);
		j++;
	}
	mini->exit_code = 1;
	if (cmd->args[0][0] == '/')
	{
		printf("minishell: No such file or directory\n");
	}
	else
		printf("minishell: %s: command not found\n", cmd->args[0]);
	free(var);
	mini->exit_code = 127;
	exit(127);
}

int	built_in_cmd_3(t_minishell	*mini, t_cmd	*cmd, char **env)
{
	//built_ins that you should not fork for
	(void)env;
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
	{
		ft_exit(cmd, mini);
		return (1);
	}
	else if ((ft_strncmp(cmd->args[0], "cd", 3) == 0) \
	&& cmd->general_info->cmd_nb == 1)
	{
		ft_cd(cmd, mini);
		return(1);
	}
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
	{
		ft_unset(cmd, mini);
		return (1);
	}
	else if ((ft_strncmp(cmd->args[0], "export", 7) == 0)  \
	&& cmd->general_info->cmd_nb == 1 && cmd->args[1])
	{
		// write(2, "hello\n", 6);
		ft_export(cmd, mini);
		return (1);
	}
	// else if (ft_strncmp(cmd->args[0], "echo", 5) == 0 && cmd->general_info->cmd_nb == 1)
	// {
	// 	mini->exit_code = 0;
	// 	ft_echo(cmd);
	// 	return (1);
	// }
	return (0);
}

void	built_in_cmd_2(t_minishell	*mini, t_cmd	*cmd, char **env)
{
	//built_ins that you should fork for
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
	{
		mini->exit_code = 0;
		ft_echo(cmd);
	}
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
	{
		mini->exit_code = 0;
		ft_pwd();
	}
	else if ((ft_strncmp(cmd->args[0], "env", 4) == 0) && cmd->general_info->cmd_nb == 1)
		ft_env(env, mini);
	else if ((ft_strncmp(cmd->args[0], "export", 7) == 0))
		ft_export(cmd, mini);
	else
	{
		execv_function(mini, cmd, env);
	}
}

int	ft_cd(t_cmd	*cmd, t_minishell	*mini)
{
	char *home;
	
	(void)mini;
	home = getenv("HOME");
	if (cmd->args[1] == NULL)
	{
		chdir(home);
	}
	else if (chdir(cmd->args[1]) != 0) 
	{
		mini->exit_code = 1;
		// mini->exit_code = 0;
		perror("minishell: ");
		return (1);
	}
	return (0);
}

void	ft_pwd()
{
	char	str[1024];

	getcwd(str, sizeof(str));
	printf("%s\n", str);
}
