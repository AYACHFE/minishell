/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:45:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/27 13:42:03 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execv_function(t_minishell	*mini, t_cmd	*cmd, char **env)
{
	(void)mini;
	int		i;
	int		j;
	char	*path;
	char	**var = NULL;


	i = 0;
	j = 0;
	path = ft_strjoin("/bin/", cmd[0].args[0]);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			var = ft_split(ft_substr(env[i], 5, ft_strlen(env[i])), ':');
			break ;
		}
		i++;
	}
	while (j < i)
	{
		if (access(var[j], F_OK) == 0)
		{
			if (fork() == 0)
			{
				execve(path, cmd[0].args, env);
				exit(0);
			}
		}
		j++;
	}

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

void	built_in_cmd(t_minishell	*mini, char **env)
{
	int 	status;
	char	*str;
	t_cmd	*cmd;

	(void)mini;
	(void)env;
	str = readline("MINISHELL-3.2$ ");
	//
	char	*s;
	char	*var;
	char	**ret;
	s = ft_strdup(str);
	var = prep(s);
	ret = ft_split(var, 11);
	mini->cmd = ret;
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
	built_in_cmd_2(mini, cmd, env);
	ft_check_dollar(mini);

	add_history(str);
	wait(&status);
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
