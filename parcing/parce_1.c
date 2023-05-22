/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:59:12 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/22 21:24:43 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//you should split the readline return with ("" , '', |, <<, >>, <, >)

void	parcing(t_minishell	*mini, char *s)
{
	int		i;
	char	**ret;
	char	*var;
	char	*str;

	i = 0;
	(void)mini;
	str = ft_strdup(s);
	var = prep(str);
	ret = ft_split(var, 11);
	while (i < count(var, 11))
	{
		printf(":%s:\n", ret[i]);
		i++;
	}
}

//puts a marker at the end of every string 
char	*prep(char	*str)
{
	int	i;
	int	j;
	char	*var;
	
	var = malloc(sizeof(char) * ft_strlen(str) + 20);
	i = 0;
	j = 0;
	while (str[i])
	{
		// cotes_check(str, var, i, j);
		// third_check(str, var, i, j);
		if (((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
			str[i] = 11;
		else if (str[i] == '"')
		{
			if (((str[i - 1] >= 9 && str[i - 1] <= 13) || str[i - 1] == 32))
				str[i - 1] = 11;
			var[j - 1] = str[i - 1];
			var[j] = str[i];
			i++;
			j++;
			while (str[i] != '"')
				var[j++] = str[i++];
		}
		else if (str[i] == '\'')
		{
			if (((str[i - 1] >= 9 && str[i - 1] <= 13) || str[i - 1] == 32))
				str[i - 1] = 11;
			var[j - 1] = str[i - 1];
			var[j] = str[i];
			i++;
			j++;
			while (str[i] != '\'')
				var[j++] = str[i++];
		}
		if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
		{
			var[j] = 11;
			var[++j] = str[i];
			var[++j] = str[++i];
			var[++j] = 11;
		}
		else if ((str[i] == '|' || str[i] == '>' || str[i] == '<' || (str[i] == '>' && \
		str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')))
		{
			var[j] = 11;
			var[++j] = str[i];
			var[++j] = 11;
		}
		else
			var[j] = str[i];
		i++;
		j++;
		var[j] = '\0';
	}
	return (var);
}
