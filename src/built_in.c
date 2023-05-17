/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:45:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/17 10:25:29 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char **ft_env(char **env, t_minishell *mini)
{
	int i;

	i = 0;
	while(env[i])
		i++;
	mini->my_env = malloc(sizeof(char *) *(i + 1));
	i = 0;
	while(env[i])
	{
		mini->my_env[i] = ft_strdup(env[i]);
		i++;	
	}
	mini->my_env[i] = 0;
	return(mini->my_env);
}


void	built_in_cmd_2(t_minishell	*mini, char **env)
{
	char	*args[10];

	args[0] = ft_strdup("ls");
	args[1] = NULL;
	if (ft_strncmp(mini->str[0], "echo", ft_strlen(mini->str[0])) == 0)
		ft_echo(mini);
	else if (ft_strncmp(mini->str[0], "cd", ft_strlen(mini->str[0])) == 0)
		ft_cd(mini);
	else if (ft_strncmp(mini->str[0], "pwd", ft_strlen(mini->str[0])) == 0)
		ft_pwd();
	// else if (ft_strncmp(mini->str[0], "exit", ft_strlen(mini->str[0])) == 0)
	// 	exit(42);
	else if (ft_strncmp(mini->str[0], "env", ft_strlen(mini->str[0])) == 0)
		ft_env(env);
	else if (ft_strncmp(mini->str[0], "ls", ft_strlen(mini->str[0])) == 0)
		execve("/bin/ls", args, env);
	else
		perror(mini->str[0]);
}

void	built_in_cmd(t_minishell	*mini, char **env)
{
	int 	status;
	char	*str;

	str = readline("MINISHELL-3.2$ ");
	mini->str = ft_split(str, ' ');
	ft_env(env, &mini);
	if (ft_strncmp(mini->str[0], "exit", ft_strlen(mini->str[0])) == 0)
		exit(42);
	if ((fork() == 0))
	{
		built_in_cmd_2(mini, env);
	}
	wait(&status);
	// if (WIFEXITED(status) != 0)
	// {
	// 	printf("%d\n", WEXITSTATUS(status));
	// 	if (WEXITSTATUS(status) == 42)
	// 		exit (0);
	// }
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
		perror("cd");
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

void	ft_env(char	**env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}	
}