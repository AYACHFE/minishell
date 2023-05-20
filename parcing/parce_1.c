/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:59:12 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/20 21:46:01 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//you should split the readline return with ("" , '', |, <<, >>, <, >)

void	parcing(t_minishell	*mini, char *str)
{
	int		i;
	// char	**ret;

	i = 0;
	(void)mini;
	// space_eleminator(str);
	// ret = ft_split(str, ' ');
	// printf("%s\n", ret[1]);
	place_np(str);
}

void	space_to_imprint(char	*str, int i)
{
	int	j;

	j = 0;
	while (str[i] != '"')
	{
		if (str[i] == 32)
			str[i] = 11;
		i++;
	}
}

char	*space_eleminator(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			space_to_imprint(str, i);
		i++;
	}
	return (str);
}

//still not working properly
void	place_np(char	*str)
{
	int	i;
	int	check;
	
	check = 0;
	i = 0;
	while (str[i])
	{
		if (((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) && str[i + 1] == 32)
			str[i + 1] = '?';
		else if (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i + 1] != 32)
			str[i] = '?';
		else if (str[i] == '"' && check == 0)
		{
			str[i - 1] = '?';
			while (str[i] != '"')
				i++;
			str[i] = '?';
		}
		else if (str[i] == '\'' && check == 0)
		{
			str[i - 1] = '?';
			while (str[i] != '\'')
				i++;
			str[i + 1] = '?';
		}
		i++;
	}
	str[i] = '\0';
	printf("%s\n", str);
}
