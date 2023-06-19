/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.1_ext.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:19:26 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/19 12:28:14 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error_here_document_pr2_ext(int l)
{
	if (l == 1)
		ft_putstr_fd("minishell: command not found\n", 2);
	else
		ft_putstr_fd("minishell: syntax error\n", 2);
	return ;
}

int	ft_error_here_document_pr2(char *s, int l)
{
	int	i;

	i = 0;
	if (s[0] == '<' && s[1] == '<' && s[2] == '\0')
	{
		ft_error_here_document_pr2_ext(l);
		return (0);
	}
	if (s[i] == '<' && s[i + 1] == '<')
	{
		i = i + 2;
		while (s[i] == ' ')
			i++;
		if (s[i] == '|')
		{
			if (l == 1)
				ft_putstr_fd("minishell: command not found\n", 2);
			else
				ft_putstr_fd("minishell: syntax error\n", 2);
			return (0);
		}
	}
	return (1);
}

int	ft_error_here_document_pr3(char *s, int l)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '<' && s[i + 1] == '<') && (s[i + 2] == '\0' \
		|| (s[i + 2] == '|' || (s[i + 1] == '>' && s[i + 2] == '<'))))
		{
			if (l == 1)
				ft_putstr_fd("minishell: command not found\n", 2);
			else
				ft_putstr_fd("minishell: syntax error\n", 2);
			return (0);
		}
		if (s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '\0')
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

int	ft_error_here_document(char *s, int l)
{
	if (ft_error_here_document_pr2(s, l) == 0)
		return (0);
	if (ft_error_here_document_pr3(s, l) == 0)
		return (0);
	return (1);
}

int	ft_error(char *str, int i)
{
	int	ret;

	ret = ft_error_pipe(str);
	if (ret == 2)
		return (2);
	if (ret == 0)
		return (0);
	if (ft_double_single_quote(str) == 0)
		return (0);
	if (ft_error_appends(str, i) == 0)
		return (0);
	if (ft_error_here_document(str, i) == 0)
		return (0);
	if (ft_error_output(str, i) == 0)
		return (0);
	if (ft_error_input(str, i) == 0)
		return (0);
	return (1);
}
