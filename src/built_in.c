/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:45:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/27 20:29:28 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// the engine of this program
void	built_in_cmd(t_minishell	*mini, char **env)
{
	char	*str;
	t_cmd	*cmd;
	
	char	*s;
	char	*var;
	char	**ret;

	(void)mini;
	(void)env;
	str = readline("MINISHELL-3.2$ ");
	//
	s = ft_strdup(str);
	var = prep(s);
	ret = ft_split(var, 11);
	mini->cmd = ret;
	mini->cmd_nb = count(var, 11);
	cmd = malloc(sizeof(t_cmd) * cmd_counter(mini));
	//
	
	mini->count_str = 0;
	if (ft_strlen(str) == 0)
		return ;
	mini->str = ft_split(str, ' ');
	mini->count_str = count(str, ' ');
	if (ft_error(str) == 0)
		return ;
	parcing(mini, cmd, str);
	ft_check_dollar(mini);

	exec_1(mini, cmd, env);

	add_history(str);
	wait(NULL);
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
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			var = ft_split(ft_substr(env[i], 5, ft_strlen(env[i])), ':');
			break ;
		}
		i++;
	}
	path_nb = count(ft_substr(env[i], 5, ft_strlen(env[i])), ':');
	while (j < path_nb)
	{
		val = ft_strjoin(var[j], "/");
		val = ft_strjoin(val, cmd->args[0]);
		if (access(val, F_OK) == 0)
		{
			execve(val, cmd->args, env);
			free(var[j]);
			free(var);
			free(val);
			exit(0);
		}
		free(var[j]);
		free(val);
		j++;
	}
	free(var);
}

void	execv_function_fork(t_minishell	*mini, t_cmd	*cmd, char **env)
{
	(void)mini;
	int		i;
	int		j;
	int		path_nb;
	char	**var = NULL;
	char	*val;


	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			var = ft_split(ft_substr(env[i], 5, ft_strlen(env[i])), ':');
			break ;
		}
		i++;
	}
	path_nb = count(ft_substr(env[i], 5, ft_strlen(env[i])), ':');
	while (j < path_nb)
	{
		val = ft_strjoin(var[j], "/");
		val = ft_strjoin(val, cmd->args[0]);
		if (access(val, F_OK) == 0)
		{
			if (fork() == 0)
			{
				execve(val, cmd->args, env);
				free(var[j]);
				free(var);
				free(val);
				exit(0);
			}
		}
		free(var[j]);
		free(val);
		j++;
	}
	free(var);
}

void	built_in_cmd_2(t_minishell	*mini, t_cmd	*cmd, char **env)
{
	(void)cmd;
	if (ft_strncmp(mini->str[0], "exit", ft_strlen(mini->str[0])) == 0)
		exit(42);
	else if (ft_strncmp(mini->str[0], "echo", ft_strlen(mini->str[0])) == 0)
		ft_echo(mini);
	else if (ft_strncmp(mini->str[0], "cd", ft_strlen(mini->str[0])) == 0)
		ft_cd(mini);
	else if (ft_strncmp(mini->str[0], "pwd", ft_strlen(mini->str[0])) == 0)
		ft_pwd();
	else if (ft_strncmp(mini->str[0], "env", ft_strlen(mini->str[0])) == 0)
		ft_env(env, mini);
	else if (ft_strncmp(mini->str[0], "unset", ft_strlen(mini->str[0])) == 0)
		ft_unset(mini);
	else if (ft_strncmp(mini->str[0], "export", ft_strlen(mini->str[0])) == 0)
		ft_export(mini);
	else
		execv_function(mini, cmd, env);
}

void	built_in_cmd_fork(t_minishell	*mini, t_cmd	*cmd, char **env)
{
	(void)cmd;
	if (ft_strncmp(mini->str[0], "exit", ft_strlen(mini->str[0])) == 0)
		exit(42);
	else if (ft_strncmp(mini->str[0], "echo", ft_strlen(mini->str[0])) == 0)
		ft_echo(mini);
	else if (ft_strncmp(mini->str[0], "cd", ft_strlen(mini->str[0])) == 0)
		ft_cd(mini);
	else if (ft_strncmp(mini->str[0], "pwd", ft_strlen(mini->str[0])) == 0)
		ft_pwd();
	else if (ft_strncmp(mini->str[0], "env", ft_strlen(mini->str[0])) == 0)
		ft_env(env, mini);
	else if (ft_strncmp(mini->str[0], "unset", ft_strlen(mini->str[0])) == 0)
		ft_unset(mini);
	else if (ft_strncmp(mini->str[0], "export", ft_strlen(mini->str[0])) == 0)
		ft_export(mini);
	else
		execv_function_fork(mini, cmd, env);
}

int	ft_cd(t_minishell	*mini)
{
	char *home;
	
	home = getenv("HOME");
	if (!mini->str[1])
	{
		chdir(home);
	}
	else if (chdir(mini->str[1]) != 0) 
	{
		perror("-minishell: cd");
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
