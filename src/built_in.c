/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:45:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/17 15:28:49 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// the engine of this program
void	built_in_cmd(t_minishell	*mini, char **env)
{
	char	*str;
	t_cmd	*cmd;
	char	*s;
	char	*var;
	char	**ret;

	str = readline("\033[0;34mMINISHELL-3.2$ \033[0m");
	if (!str)
		exit(mini->exit_code);
	if (count(str, ' ') == 0)
	{
		free(str);
		return ;
	}
	add_history(str);
	if (first_error_part(mini, str) == 1)
	{
		free(str);
		return ;
	}
	s = ft_strdup(str);
	var = prep(s, mini);
	ret = ft_split(var, 11);
	mini->cmd = ret;
	mini->cmd_nb = count(var, 11);
	if (ft_error_2(mini) == 1)
		return ;
	cmd = malloc(sizeof(t_cmd) * cmd_counter(mini));
	ft_check_dollar(mini);
	parcing(mini, cmd, str);
	exec_1(mini, cmd, env);
	to_free_1(mini, ret, var, str, s);
	to_free(cmd);
	// system("leaks minishell");
}

//built_ins that you should not fork for
int	built_in_cmd_3(t_minishell	*mini, t_cmd	*cmd, char **env)
{
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
		return (1);
	}
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
	{
		ft_unset(cmd, mini);
		return (1);
	}
	else if ((ft_strncmp(cmd->args[0], "export", 7) == 0) \
	&& cmd->general_info->cmd_nb == 1 && cmd->args[1])
	{
		ft_export(cmd, mini);
		return (1);
	}
	return (0);
}

//built_ins that you should fork for
void	built_in_cmd_2(t_minishell	*mini, t_cmd	*cmd, char **env)
{
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		ft_exit(cmd, mini);
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
		execv_function(mini, cmd);
}
