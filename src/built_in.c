/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:45:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/19 15:41:34 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_in_cmd_2(t_minishell	*mini, char **env)
{
	char	*args[10];

	args[0] = ft_strdup("ls");
	args[1] = NULL;
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
		perror(mini->str[0]);
}

void	built_in_cmd(t_minishell	*mini, char **env)
{
	int 	status;
	char	*str;
	char	*args[10];

	args[0] = ft_strdup("ls");
	args[1] = NULL;
	str = readline("MINISHELL-3.2$ ");
	str = ft_strtrim(str, " ");
	mini->count_str = 0;
	if (ft_strlen(str) == 0)
		return ;
	mini->str = ft_split(str, ' ');
	mini->count_str = count(str, ' ');
	built_in_cmd_2(mini, env);
	add_history(str);
	if ((fork() == 0 && ft_strncmp(mini->str[0], "ls", ft_strlen(mini->str[0])) == 0))
	{
		execve("/bin/ls", args, env);
	}
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
