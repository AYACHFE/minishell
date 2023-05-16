/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:45:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/16 21:20:43 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_in_cmd(t_minishell	*mini, char **env)
{
	int 	status;
	char	*str;
	char	*args[10];

	args[0] = ft_strdup("ls");
	args[1] = NULL;
	str = readline("MINISHELL-3.2$ ");
	mini->str = ft_split(str, ' ');
	if ((fork() == 0))
	{
		if (ft_strncmp(mini->str[0], "echo", ft_strlen(mini->str[0])) == 0)
		{
			ft_echo(str);
		}
		else if (ft_strncmp(mini->str[0], "cd", ft_strlen(mini->str[0])) == 0)
		{
			ft_cd(mini);
		}
		else if (ft_strncmp(mini->str[0], "pwd", ft_strlen(mini->str[0])) == 0)
		{
			ft_pwd();
		}
		else if (ft_strncmp(mini->str[0], "exit", ft_strlen(mini->str[0])) == 0)
		{
			puts("---");
			exit(42);
		}
		else if (ft_strncmp(mini->str[0], "env", ft_strlen(mini->str[0])) == 0)
		{
			ft_env(env);
		}
		else if ((str[0] == 'l' && str[1] == 's'))
		{
			execve("/bin/ls", args, env);
		}
		else
		{
			perror(str);
		}
	}
	wait(&status);
	if (WIFEXITED(status) != 0)
	{
		// printf("---<<%d\n", WEXITSTATUS(status));
		if (WEXITSTATUS(status) == 42)
			exit (0);	
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