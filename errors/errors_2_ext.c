/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:51:56 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/18 15:03:57 by aachfenn         ###   ########.fr       */
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

int	check_first_cmd_ext(char	*s, int i, int check)
{
	if (s[i] == '|' && check == 2)
	{
		ft_putendl_fd("minishell: command not found", 2);
		return (2);
	}
	return (0);
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
		if (check_first_cmd_ext(s, i, check) == 2)
			return (2);
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
		if (check_first_cmd_ext(s, i, check) == 2)
			return (2);
	}
	return (0);
}
