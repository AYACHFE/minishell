/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:45:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/12 21:21:54 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// the engine of this program
void	built_in_cmd(t_minishell	*mini, char **env)
{
	// int		i;
	char	*str;
	t_cmd	*cmd;
	// t_cmd	*cmd = NULL;
	
	char	*s;
	char	*var;
	char	**ret;
	mini->center_sp = 0;
	mini->right_sp = 0;
	mini->left_sp = 0;

	(void)mini;
	(void)env;
	str = readline("\033[0;34mMINISHELL-3.2$ \033[0m");
	if (!str)
		exit(mini->exit_code);
	add_history(str);
	if (first_error_part(mini, str) == 1)
		return ;
	s = ft_strdup(str);
	var = prep(s);
	ret = ft_split(var, 11);
	mini->cmd = ret;
	mini->cmd_nb = count(var, 11);
	if (ft_error_2(mini) == 1)
		return ;
	cmd = malloc(sizeof(t_cmd) * cmd_counter(mini));
	ft_check_dollar(mini);
	parcing(mini, cmd, str);
	if (count(str, ' ') > 0)
		exec_1(mini, cmd, env);
	
	// ft_free_1();
	// i = 0;
	// while (ret[i])
	// 	free(ret[i++]);
	// i = 0;
	// int j = 0;
	// while (i < cmd->general_info->cmd_nb)
	// {
	// 	j = 0;
	// 	while (cmd[i].args[j])
	// 		free(cmd[i].args[j++]);
	// 	// j = 0;
	// 	// while (cmd[i].files[j])
	// 	// 	free(cmd[i].files[j++]);
	// 	// j = 0;
	// 	// while (cmd[i].eof[j])
	// 	// 	free(cmd[i].eof[j++]);
	// 	free(cmd[i].args);
	// 	// free(cmd[i].files);
	// 	// free(cmd[i].eof);
	// 	i++;
	// }
	// free(ret);
	// free(var);
	// free(str);
	// free(cmd);
	// free(cmd->general_info);
}

int	built_in_cmd_3_check(t_minishell	*mini, t_cmd	*cmd, char **env)
{
	//built_ins that you should not fork for
	(void)env;
	(void)mini;
	if ((ft_strncmp(cmd->args[0], "exit", 5) == 0) && cmd->general_info->cmd_nb == 1)
	{
		// ft_exit(cmd, mini);
		return (1);
	}
	else if ((ft_strncmp(cmd->args[0], "cd", 3) == 0) \
	&& cmd->general_info->cmd_nb == 1)
	{
		// ft_cd(cmd, mini);
		return(1);
	}
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
	{
		// ft_unset(cmd, mini);
		return (1);
	}
	else if ((ft_strncmp(cmd->args[0], "export", 7) == 0)  \
	&& cmd->general_info->cmd_nb == 1 && cmd->args[1])
	{
		// ft_export(cmd, mini);
		return (1);
	}
	return (0);
}

int	built_in_cmd_3(t_minishell	*mini, t_cmd	*cmd, char **env)
{
	//built_ins that you should not fork for
	(void)env;
	if ((ft_strncmp(cmd->args[0], "exit", 5) == 0) && cmd->general_info->cmd_nb == 1)
	{
		ft_exit(cmd, mini);
		return (1);
	}
	else if ((ft_strncmp(cmd->args[0], "cd", 3) == 0) \
	&& cmd->general_info->cmd_nb == 1)
	{
		ft_cd(cmd, mini);
		return(1);
	}
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
	{
		ft_unset(cmd, mini);
		return (1);
	}
	else if ((ft_strncmp(cmd->args[0], "export", 7) == 0)  \
	&& cmd->general_info->cmd_nb == 1 && cmd->args[1])
	{
		ft_export(cmd, mini);
		return (1);
	}
	return (0);
}

void	built_in_cmd_2(t_minishell	*mini, t_cmd	*cmd, char **env)
{
	//built_ins that you should fork for
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		ft_exit(cmd, mini);
	/////
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
	{
		mini->exit_code = 0;
		ft_echo(cmd);
	}
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
	{
		mini->exit_code = 0;
		ft_pwd();
	}
	else if ((ft_strncmp(cmd->args[0], "env", 4) == 0) && cmd->general_info->cmd_nb == 1)
		ft_env(env, mini);
	else if ((ft_strncmp(cmd->args[0], "export", 7) == 0))
		ft_export(cmd, mini);
	else
	{
		execv_function(mini, cmd, env);
	}
}

int	ft_cd(t_cmd	*cmd, t_minishell	*mini)
{
	char *home;
	
	(void)mini;
	home = getenv("HOME");
	int	i = 0;
	int	check = 0;
	while (mini->my_env[i] != NULL)
	{
		if (ft_strncmp(mini->my_env[i], "HOME", ft_cnt(mini->my_env[i])) == 0)
		{
			check = 1;
			break ;
		}
		i++;
	}
	if (check == 0 && !(cmd->args[1]))
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (cmd->args[1] == NULL)
	{
		chdir(home);
	}
	else if (chdir(cmd->args[1]) != 0) 
	{
		mini->exit_code = 1;
		perror("minishell: ");
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
