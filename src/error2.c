/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:54:00 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/09 12:14:55 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_first_cmd(char	*s)
{
	if (check_first_cmd_d(s) == 2)
		return (2);
	if (check_first_cmd_s(s) == 2)
		return (2);
	return (1);
}

int	check_first_cmd_d(char	*s)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (s[i] == 32)
		i++;
	if (s[i] == '"')
	{
		check++;
		i++;
		while (s[i] == 32 || s[i] == '"')
		{
			if (s[i] == '"')
				check++;
			i++;
		}
		while (s[i] == 32)
			i++;
		if (s[i] == '|' && check == 2)
		{
			ft_putendl_fd("minishell: command not found", 2);
			return (2);
		}
	}
	return (0);
}

int	check_first_cmd_s(char	*s)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (s[i] == 32)
		i++;
	if (s[i] == '\'')
	{
		check++;
		i++;
		while (s[i] == 32 || s[i] == '\'')
		{
			if (s[i] == '\'')
				check++;
			i++;
		}
		while (s[i] == 32)
			i++;
		if (s[i] == '|' && check == 2)
		{
			ft_putendl_fd("minishell: command not found", 2);
			return (2);
		}
	}
	return (0);
}

int	pipes_error(t_minishell	*mini, int i)
{
	if (mini->cmd[i][0] == '|' && mini->cmd[i + 1] == NULL)
	{
		ft_putendl_fd("minishell: syntax error", 2);
		mini->exit_code = 2;
		return (1);
	}
	if ((mini->cmd[i][0] == '"' && mini->cmd[i][1] == '"') && mini->cmd[i + 1][0] == '|')
	{
		ft_putendl_fd("minishell: command not found", 2);
		mini->exit_code = 0;
		return (1);
	}
	if ((mini->cmd[i][0] == '\'' && mini->cmd[i][1] == '\'') && mini->cmd[i + 1][0] == '|')
	{
		ft_putendl_fd("minishell: command not found", 2);
		mini->exit_code = 0;
		return (1);
	}
	if ((mini->cmd[i][0] == '>' && mini->cmd[i][1] == '>') && mini->cmd[i + 1][0] == '|')
	{
		ft_putendl_fd("minishell: syntax error", 2);
		mini->exit_code = 2;
		return(1);
	}
	return (0);
}

int	more_pipes_error(t_minishell	*mini, int i)
{
	if (mini->cmd[i][0] == '>' && mini->cmd[i + 1][0] == '|')
	{
		ft_putendl_fd("minishell: syntax error", 2);
		mini->exit_code = 2;
		return(1);
	}
	if (mini->cmd[i][0] == '<' && mini->cmd[i + 1][0] == '|')
	{
		ft_putendl_fd("minishell: syntax error", 2);
		mini->exit_code = 2;
		return(1);
	}
	if (mini->cmd[i][0] == '|' && (mini->cmd[i + 1][0] == '"' && mini->cmd[i + 1][1] == '"'))
	{
		ft_putendl_fd("minishell: command not found", 2);
		mini->exit_code = 127;
		return(1);
	}
	if (mini->cmd[i][0] == '|' && (mini->cmd[i + 1][0] == '\'' && mini->cmd[i + 1][1] == '\''))
	{
		ft_putendl_fd("minishell: command not found", 2);
		mini->exit_code = 127;
		return(1);
	}
	return (0);
}

int	ft_error_2(t_minishell	*mini)
{
	int	i;

	i = 0;
	while (mini->cmd[i])
	{
		if (pipes_error(mini, i) == 1)
			return (1);
		if (more_pipes_error(mini, i) == 1)
			return (1);
		i++;
	}
	return (0);
}