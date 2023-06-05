/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:08:09 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/05 12:03:51 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_cmd	*cmd, t_minishell	*mini)
{
	int	i;

	i = 0;
	while (cmd->args[i])
		i++;
	// printf("i == %d\n", i);
	if (cmd->args[1] && cmd->args[1][0] == '0')
		exit(0);
	// printf("atoi %d\n", ft_toint_check(cmd->args[1]));
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
	{
		if (ft_toint_check(cmd->args[1]) > 0)
			exit(ft_toint_check(cmd->args[1]));
		else
			exit(255);
	}
	else
		exit(mini->exit_code);
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
	// while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	// 	i++;
	if (str[i] == '-')
	{
		// return (0);
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