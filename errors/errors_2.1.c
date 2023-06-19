/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:45:20 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/19 12:46:18 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	more_pipes_error_exc(t_minishell	*mini, int i)
{
	if (mini->cmd[i][0] == '>' && mini->cmd[i + 1][0] == '|')
	{
		ft_putendl_fd("minishell: syntax error", 2);
		mini->exit_code = 2;
		return (1);
	}
	if (mini->cmd[i][0] == '<' && mini->cmd[i + 1][0] == '|')
	{
		ft_putendl_fd("minishell: syntax error", 2);
		mini->exit_code = 2;
		return (1);
	}
	return (0);
}

int	more_pipes_error(t_minishell	*mini, int i)
{
	if (more_pipes_error_exc(mini, i) == 1)
		return (1);
	if (mini->cmd[i][0] == '|' && (mini->cmd[i + 1][0] == '"' \
		&& mini->cmd[i + 1][1] == '"'))
	{
		ft_putendl_fd("minishell: command not found", 2);
		mini->exit_code = 127;
		return (1);
	}
	if (mini->cmd[i][0] == '|' && (mini->cmd[i + 1][0] == '\'' \
		&& mini->cmd[i + 1][1] == '\''))
	{
		ft_putendl_fd("minishell: command not found", 2);
		mini->exit_code = 127;
		return (1);
	}
	return (0);
}
