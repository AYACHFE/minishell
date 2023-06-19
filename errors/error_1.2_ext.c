/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1,2_ext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:12:07 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/19 12:20:27 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_error_input_pr3(char *s, int l)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '<' && (s[i + 1] == '\0' || (s[i + 1] == '|' \
		|| (s[i + 1] == '<' && s[i + 2] == '<'))))
		{
			if (l == 1)
				ft_putstr_fd("minishell: command not found\n", 2);
			else
				ft_putstr_fd("minishell: syntax error\n", 2);
			return (0);
		}
		if (s[i] == '<' && s[i + 1] == '\0')
		{
			if (l == 1)
				ft_putstr_fd("minishell: command not found\n", 2);
			else
				ft_putstr_fd("minishell: syntax error\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_error_input(char *s, int l)
{
	if (ft_error_input_pr2(s, l) == 0)
		return (0);
	if (ft_error_input_pr3(s, l) == 0)
		return (0);
	return (1);
}

int	ft_error_appends_pr2(char *s, int l)
{
	int	i;

	i = 0;
	if (s[0] == '>' && s[1] == '>' && s[2] == '\0')
	{
		if (l == 1)
			ft_putstr_fd("minishell: command not found\n", 2);
		else
			ft_putstr_fd("minishell: syntax error\n", 2);
		return (0);
	}
	return (1);
}

int	ft_error_appends_pr3(char *s, int l)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '>' && s[i + 1] == '>') && (s[i + 2] == '\0' \
		|| (s[i + 2] == '|' || (s[i + 1] == '>' && s[i + 2] == '<'))))
		{
			if (l == 1)
				ft_putstr_fd("minishell: command not found\n", 2);
			else
				ft_putstr_fd("minishell: syntax error\n", 2);
			return (0);
		}
		if (s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '\0')
		{
			if (l == 1)
				ft_putstr_fd("minishell: command not found\n", 2);
			else
				ft_putstr_fd("minishell: syntax error\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_error_appends(char *s, int l)
{
	if (ft_error_appends_pr2(s, l) == 0)
		return (0);
	if (ft_error_appends_pr3(s, l) == 0)
		return (0);
	return (1);
}
