/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:45:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/17 19:07:15 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_env(char **env, t_minishell *mini)
{
	int i;

	i = 0;
	while(env[i])
	{
		mini->my_env[i] = ft_strdup(env[i]);
		printf("%s\n", mini->my_env[i]);
		i++;	
	}
}

char **ft_env_1(char **env, t_minishell *mini)
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
	return (mini->my_env);
}


void	built_in_cmd_2(t_minishell	*mini, char **env)
{
	char	*args[10];

	args[0] = ft_strdup("ls");
	args[1] = NULL;
	ft_env_1(env, mini);
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
		built_in_cmd_2(mini, env);
	}
	wait(&status);
	if (WIFEXITED(status) != 0)
	{
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

int ft_cnt (char *str)
{
	int i;
	i = 0;
	while(str[i] != '=' && str[i] != '\0')
		i++;
	return(i);	
}

void	ft_unste(t_minishell *mini)
{
	int		i;
	int		j;
	int		l;

	i = 0;
	l = 0;
	while(mini->str[i])
	{	
		j = 0;
		while(mini->my_env[j])
		{
			if (ft_strncmp(mini->str[i], mini->my_env[j], ft_cnt(mini->str[i])) != 0)
				j++;
			else
			{
				j++;
				l++;
				break;
			}
		}
		i++;
	}
	ft_rem_var(mini->str, mini, l);
}

void	ft_rem_var(char **str, t_minishell *mini, int l)
{
	int 	i;
	int		j;
	int		d;
	char 	**my_tmp;

	j = 0;
	while (mini->my_env[j])
		j++;
	my_tmp = malloc(sizeof(char *) * (j - l + 1));
	d = 0;
	j = 0;
	while(mini->my_env[d])
	{
		i = 1;
		while (i <= mini->count_str)
		{

			if (ft_strncmp(str[i], mini->my_env[d], ft_cnt(str[i])) != 0)
			{
				my_tmp[j] = ft_strdup(mini->my_env[d]);
				// printf("%s\n", my_tmp[j]);
				j++;
				break;
			}
			else
				i++;
		}
		d++;
	}
	my_tmp[j] = 0;
	i = 0;
	printf("%s\n", mini->my_env[i]);
	while (mini->my_env[i])
	{
		printf("----------------------------------\n");
		printf("------>%s\n", my_tmp[i]);
		free(mini->my_env[i]);
		i++;
	}
	free(mini->my_env);
	ft_env_1(my_tmp, mini);
	// mini->my_env = malloc(sizeof(char *) * (j - l + 1));
}