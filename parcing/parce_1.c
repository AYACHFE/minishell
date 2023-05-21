/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:59:12 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/21 14:55:24 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//you should split the readline return with ("" , '', |, <<, >>, <, >)

void	parcing(t_minishell	*mini, char *str)
{
	int		i;
	char	**ret;
	char	*var;

	i = 0;
	(void)mini;
	space_to_imprint_dcotes(str);
	space_to_imprint_scotes(str);
	prep(str);
	var = unwanted_spaces(str);
	return_umprint_to_space(var);
	// printf("var == :%s:\n", var);
	ret = ft_split(var, 11);
	while (i < count(var, 11))
	{
		printf(";%s;\n", ret[i]);
		i++;
	}
}

void	return_umprint_to_space(char	*var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '~')
			var[i] = 32;
		i++;
	}
}

//skips the spaces that aren't betwen "" or ''
char	*unwanted_spaces(char	*str)
{
	int	i;
	int	j;
	char	*re;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != 32)
			j++;
		i++;
	}
	re = malloc(sizeof(char) * j);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != 32)
		{
			re[j] = str[i];
			j++;
		}
		i++;
	}
	return (re);
}

//return the spaces that are betwen **double** cotes to an inprintable character
void	space_to_imprint_dcotes(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i])
			{
				if (str[i] == '"')
					break ;
				else if (str[i] == 32)
					str[i] = '~';
				i++;
			}
		}
		i++;
	}
	// printf("%s\n", str);
}

//return the spaces that are betwen *single* cotes to an inprintable character
void	space_to_imprint_scotes(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i])
			{
				if (str[i] == '"')
					break ;
				else if (str[i] == 32)
					str[i] = '~';
				i++;
			}
		}
		i++;
	}
	// printf("%s\n", str);
}

//puts a marker at the end of every string 
void	prep(char	*str)
{
	int	i;
	int	check;
	
	check = 0;
	i = 0;
	while (str[i])
	{
		if (((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) && str[i + 1] == 32)
			str[i + 1] = 11;
		else if (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i + 1] != 32)
			str[i] = 11;
		else if (str[i] == '"' && check == 0)
		{
			str[i - 1] = 11;
			i++;
			while (str[i] != '"')
				i++;
			str[i + 1] = 11;
		}
		else if (str[i] == '\'' && check == 0)
		{
			str[i - 1] = 11;
			i++;
			while (str[i] != '\'')
				i++;
			str[i + 1] = 11;
		}
		i++;
	}
	str[i] = '\0';
	// printf("str == :%s:\n", str);
}
