/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:06:09 by rarraji           #+#    #+#             */
/*   Updated: 2023/06/19 12:44:22 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_double_single_quote_ext(char	*str, t_prep	*prep)
{
	int	c;

	if (str[prep->i] == '"' || str[prep->i] == '\'')
	{
		prep->check = 0;
		prep->j = prep->i + 1;
		c = str[prep->i];
		while (str[prep->j])
		{
			if (str[prep->j] == c)
			{
				prep->check = 1;
				break ;
			}
			else
				prep->j++;
		}
		prep->i = prep->j + 1;
	}
	else
		prep->i++;
}

int	ft_double_single_quote(char *str)
{
	t_prep	prep;

	prep.i = 0;
	prep.j = 0;
	prep.check = 1;
	while (str[prep.i])
	{
		ft_double_single_quote_ext(str, &prep);
	}
	if (prep.check == 0)
	{
		ft_putstr_fd("minishell: unexpected ", 2);
		ft_putstr_fd("EOF while looking for matching\n", 2);
	}
	return (prep.check);
}

int	ft_error_pipe_par2(char *s, int *i)
{
	*i = 0;
	if (check_first_cmd(s) == 2)
		return (2);
	*i = 0;
	while (s[*i] == '\"' || s[*i] == '\'' || s[*i] == ' ')
	{
		(*i)++;
	}
	if (s[*i] == '|')
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (0);
	}
	if (s[0] == '|' && s[1] == '\0')
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (0);
	}
	return (1);
}

int	ft_error_pipe_par3(char *s, int i)
{
	while (s[i])
	{
		if (s[i] == '|' && (s[i + 1] == '\0' || (s[i + 1] == '>' \
		|| (s[i + 1] == '>' && s[i + 2] == '>'))))
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			return (0);
		}
		if (s[i] == '|' && (s[i + 1] == '\0'))
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			return (0);
		}
		if ((s[i] == '|' && s[i + 1] == ' ' && s[i + 2] == '|') \
		|| (s[i] == '|' && s[i + 1] == '|'))
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_error_pipe(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = ft_error_pipe_par2(s, &i);
	if (j == 0)
		return (0);
	if (j == 2)
		return (2);
	if (ft_error_pipe_par3(s, i) == 0)
		return (0);
	return (1);
}
