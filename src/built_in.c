/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:45:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/23 19:53:07 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execv_function(t_minishell	*mini, char **env)
{
	char	*args[10];
	// char	*args_1[10];

	// args_1[0] = ft_strdup("cat");
	// args_1[1] = NULL;
	args[0] = ft_strdup("ls");
	args[1] = NULL;
	if (ft_strncmp(mini->str[0], "ls", ft_strlen(mini->str[0])) == 0)
	{
		if (fork() == 0)
			execve("/bin/ls", args, env);
	}
	else if (ft_strncmp(mini->str[0], "cat", ft_strlen(mini->str[0])) == 0)
	{
		if (fork() == 0)
		{
			// Set file descriptors
			int fd_in = open("input.txt", O_RDONLY);
			int fd_out = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			int fd_err = open("error.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd_in, 0);   // Set standard input
			dup2(fd_out, 1);  // Set standard output
			dup2(fd_err, 2);  // Set standard error
			close(fd_in);
			close(fd_out);
			close(fd_err);
			// Execute "cat" command
			char* args_2[] = { "/bin/cat", "file.txt", NULL };
			execve("/bin/cat", args_2, env);
		}
	}
	else
		perror(mini->str[0]);
}

void	built_in_cmd_2(t_minishell	*mini, char **env)
{
	
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
		execv_function(mini, env);
}

void	built_in_cmd(t_minishell	*mini, char **env)
{
	int 	status;
	char	*str;

	(void)mini;
	(void)env;
	str = readline("MINISHELL-3.2$ ");
	str = ft_strtrim(str, " ");
	mini->count_str = 0;
	if (ft_strlen(str) == 0)
		return ;
	mini->str = ft_split(str, ' ');
	mini->count_str = count(str, ' ');
	built_in_cmd_2(mini, env);
	// ft_error(str);
	// parcing(mini, str);
	
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