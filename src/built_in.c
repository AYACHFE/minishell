/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:45:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/02 22:54:25 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// the engine of this program

int ft_mycmp(char *s1, char *s2)
{
	int	i;
	int	j;

	j = 0;
	i = 0;

	while (s2[i] && s2[i] == '\"')
	{
		i++;
	}
	while (s2[i] && s2[i] != '\"')
	{
		
		if(s1[j] == s2[i])
		{
			i++;
			j++;
		}
		else
			return (1);			
	}
	return(0);
}

void	built_in_cmd(t_minishell	*mini, char **env)
{
	char	*str;
	t_cmd	*cmd;
	
	char	*s;
	char	*var;
	char	**ret;

	(void)mini;
	(void)env;

	// str = readline("MINISHELL-3.2$ ");
	str = readline("\033[1;35mMINISHELL-3.2$ \033[0m");
	if (str == NULL)
	{
		
		exit(1);
	}
	add_history(str);
	if (ft_error(str) == 0)
		return ;
	s = ft_strdup(str);
	var = prep(s);
	ret = ft_split(var, 11);
	mini->cmd = ret;
	mini->cmd_nb = count(var, 11);
	cmd = malloc(sizeof(t_cmd) * cmd_counter(mini));
	mini->count_str = 0;
	if (ft_strlen(str) == 0)
		return ;
	ft_check_dollar(mini);
	mini->str = ft_split(str, ' ');
	mini->count_str = count(str, ' ');
	parcing(mini, cmd, str);
	puts("-->");
	exec_1(mini, cmd, env);

	free(cmd);
	// free(cmd->args);
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
			free(var[j]);
			free(var);
			execve(val, cmd->args, env);
			exit(0);
		}
		free(var[j]);
		free(val);
		j++;
	}
	perror(cmd->args[0]);
	free(var);
}

void	built_in_cmd_2(t_minishell	*mini, t_cmd	*cmd, char **env)
{
	// (void)cmd;
	if (ft_mycmp(mini->str[0], "exit") == 0)
		exit(42);
	else if (ft_mycmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_mycmp(mini->str[0], "cd") == 0)
		ft_cd(cmd);
	else if (ft_mycmp(cmd->args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_mycmp(mini->str[0], "env") == 0)
		ft_env(env, mini);
	else if (ft_mycmp(cmd->args[0], "unset") == 0)
		ft_unset(cmd, mini);
	else if (ft_mycmp(cmd->args[0], "export") == 0)
		ft_export(cmd, mini);
	else
		execv_function(mini, cmd, env);
}

int	ft_cd(t_cmd	*cmd)
{
	char *home;
	
	home = getenv("HOME");
	if (cmd->args[1] == NULL)
	{
		chdir(home);
	}
	else if (chdir(cmd->args[1]) != 0) 
	{
		perror("-minishell: cd");
		return (1);
	}
	return (0);
}

// int	ft_cd(t_minishell	*mini)
// {
// 	char *home;
	
// 	home = getenv("HOME");
// 	if (!mini->str[1])
// 	{
// 		chdir(home);
// 	}
// 	else if (chdir(mini->str[1]) != 0) 
// 	{
// 		perror("-minishell: cd");
// 		return (1);
// 	}
// 	return (0);
// }

void	ft_pwd()
{
	char	str[1024];

	getcwd(str, sizeof(str));
	printf("%s\n", str);
}