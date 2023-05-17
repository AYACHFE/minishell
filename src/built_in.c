/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:45:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/17 12:35:48 by rarraji          ###   ########.fr       */
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
		printf("%s\n", mini->my_env[i]);
		i++;	
	}
	mini->my_env[i] = 0;
	return (mini->my_env);
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
		ft_env(env, mini);
	else if (ft_strncmp(mini->str[0], "ls", ft_strlen(mini->str[0])) == 0)
		execve("/bin/ls", args, env);
	else if (ft_strncmp(mini->str[0], "unset", ft_strlen(mini->str[0])) == 0)
		ft_unste(mini);
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
	printf("%d\n", mini->count_str);
	// ft_env(env, mini);
	if (ft_strncmp(mini->str[0], "exit", ft_strlen(mini->str[0])) == 0)
		exit(42);
	if ((fork() == 0))
	{
		built_in_cmd_2(mini, env);
	}
	wait(&status);
	if (WIFEXITED(status) != 0)
	{
		printf("%d\n", WEXITSTATUS(status));
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

// void	ft_env(char	**env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		printf("%s\n", env[i]);
// 		i++;
// 	}	
// }


char **ft_unste(t_minishell *mini)
{
	int		i;
	int		j;
	int		l;

	i = 1;
	l = 0;
	while(mini->str[i])
	{
		j = 0;
		while(mini->my_env[j])
		{
			if (ft_strncmp(mini->str[i], mini->my_env[j], ft_strlen(mini->str[i])) == 0)
			{
				// ft_rem_var(mini->str[i], mini);
				j++;
				l++;
			}
			else
				j++;
		}
		i++;		
	}
	ft_rem_var(mini->str, mini, l);
	return (mini->my_env);
}

// char **ft_add_var()
// {
	
// }
char **ft_rem_var(char **str, t_minishell *mini, int l)
{
	int 	i;
	int		j;
	int 	tmp1;
	char 	**my_tmp;

	i = 0;
	while (mini->my_env[i])
	{
		if (ft_strncmp(str[i], mini->my_env[i], ft_strlen(str)) == 0)
		// if (ft_strncmp(str, mini->my_env[i], ft_strlen(str)) == 0)
		{
			tmp1 = i;
			j	= 0;
			while (mini->my_env[j])
				j++;
			my_tmp = malloc(sizeof(char *) *(j - l + 1));
			j = 0;
			while(j < i)
			{
				if(j == tmp1)
					j += 1;
				my_tmp[j] = ft_strdup(mini->my_env[j]);
				printf("%s\n", my_tmp[j]);
				j++;		
			}
			my_tmp[j] = 0;	
		}
		i++;
	}
	i = 0;
	while (mini->my_env[i])
	{
		free(mini->my_env[i]);
		i++;
	}
	mini->my_env = my_tmp;
	return (mini->my_env);
}
