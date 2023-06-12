/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:54:00 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/12 19:02:58 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	first_error_part(t_minishell	*mini, char	*str)
{
	int	error;

	error = ft_error(str, 0);
	if (error == 2)
	{
		mini->exit_code = 0;
		return (1);
	}
	if (error == 0)
	{
		mini->exit_code = 2;
		return (1);
	}
	return (0);
}

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
	if (mini->cmd[i + 1] && mini->cmd[i][0] == '"' && mini->cmd[i][1] == '"' && mini->cmd[i + 1][0] == '|')
	{
		ft_putendl_fd("minishell: command not found", 2);
		mini->exit_code = 0;
		return (1);
	}
	if (mini->cmd[i + 1] && (mini->cmd[i][0] == '\'' && mini->cmd[i][1] == '\'') && mini->cmd[i + 1][0] == '|')
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
	while (i < mini->cmd_nb)
	{
		if (pipes_error(mini, i) == 1)
			return (1);
		if (more_pipes_error(mini, i) == 1)
			return (1);
		i++;
	}
	return (0);
}
// export a="   "
// echo nike > ""$a