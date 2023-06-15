/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:08:09 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/15 18:04:04 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_cmd	*cmd, t_minishell	*mini)
{
	int	i;

	i = 0;
	while (cmd->args[i])
		i++;
	if (cmd->args[1] && cmd->args[1][0] == '0')
		exit(0);
	if (cmd->args[1] && ft_toint_check(cmd->args[1]) == 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd->args[1]);
		mini->exit_code = 255;
	}
	else if (i > 2)
	{
		printf("minishell: exit: too many arguments\n");
		mini->exit_code = 1;
	}
	else if (cmd->args[1])
		ft_exit_ext(cmd);
	else
		exit(mini->exit_code);
}

void	ft_exit_ext(t_cmd	*cmd)
{
	if (ft_toint_check(cmd->args[1]) > 0)
		exit(ft_toint_check(cmd->args[1]));
	else
		exit(255);
}

int	ft_toint_check_ext(char *str, int i, int res)
{
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			return (0);
		}
		i++;
	}
	return (res);
}

int	ft_toint_check(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i + 1] && (str[i] == '+'))
		i++;
	if (!(ft_toint_check_ext(str, i, res)))
		return (0);
	res = ft_toint_check_ext(str, i, res);
	return (res * sign);
}
