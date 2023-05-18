/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:45:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/18 13:24:03 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//free the memory allocated by the split
void	free_split(t_minishell	 *mini)
{
	int	i;

	i = 0;
	while (i < mini->count_str)
	{
		free(mini->str[i]);
		i++;
	}
	free(mini->str);
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
	else if (ft_strncmp(mini->str[0], "env", ft_strlen(mini->str[0])) == 0)
		ft_env(env, mini);
	else if (ft_strncmp(mini->str[0], "ls", ft_strlen(mini->str[0])) == 0)
		execve("/bin/ls", args, env);
	else if (ft_strncmp(mini->str[0], "unset", ft_strlen(mini->str[0])) == 0)
		ft_unste(mini);
	else if (ft_strncmp(mini->str[0], "export", ft_strlen(mini->str[0])) == 0)
	{
		puts("\n\n\n\n\n");
		ft_export(mini);
	}
	else
		perror(mini->str[0]);
}

void	built_in_cmd(t_minishell	*mini, char **env)
{
	int 	status;
	char	*str;

	str = readline("MINISHELL-3.2$ ");
	str = ft_strtrim(str, " ");
	mini->count_str = 0;
	if (ft_strlen(str) == 0)
		return ;
	mini->str = ft_split(str, ' ');
	mini->count_str = count(str, ' ');
	if (ft_strncmp(mini->str[0], "exit", ft_strlen(mini->str[0])) == 0)
		exit(42);
	if ((fork() == 0))
	{
		add_history(str);
		built_in_cmd_2(mini, env);
		// if (WEXITSTATUS(status) == 42)
		// {
		// 	printf("%d\n", WEXITSTATUS(status));
		// 	exit (42);
		// }
	}
	wait(&status);
	if (WIFEXITED(status) != 0)
	{
		if (WEXITSTATUS(status) == 42)
			exit (0);
	}
	free(str);
	free_split(mini);
}	

void	ft_export(t_minishell	*mini)
{
	int	i;
	int	j;
	char **new_env;

	i = 0;
	j = 0;
	while (mini->my_env[j])
		j++;
	new_env = malloc(sizeof(char *) * j + 2);
	i = 0;
	while (mini->my_env[i])
	{
		new_env[i] = ft_strdup(mini->my_env[i]);
		i++;
	}
	new_env[i] = mini->str[1];
	i = 0;
	// while (mini->my_env[i])
	// {
	// 	free(mini->my_env[i]);
	// 	i++;
	// }
	// free(mini->my_env);
	mini->my_env = ft_env_1(new_env, mini);
	puts("====");
	// while (new_env[i])
	// {
	// 	free(mini->my_env[i]);
	// 	i++;
	// }
	// free(new_env);
	i = 0;
	puts("-----__>");
	while (mini->my_env[i])
	{
		printf("%s\n", mini->my_env[i]);
		i++;
	}
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
