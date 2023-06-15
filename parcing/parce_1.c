/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:59:12 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/15 19:52:54 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//you should split the readline return with ("" , '', |, <<, >>, <, >)

void	parcing(t_minishell	*mini, t_cmd	*cmd, char *s)
{
	(void)mini;
	(void)s;
	to_struct(mini, cmd);
}

void	prep_ext_1(t_minishell	*mini, char	*str, char	*var , int *i, int *j)
{
	int	k;

	k = 0;
	puts("---->");
	if (str[*i] && (str[*i] == '<' && str[*i + 1] == '<') && (str[*i + 2] == '"'))
	{
		mini->do_not_exp = 1;
		var[*j] = 11;
		var[++(*j)] = str[*i];
		var[++(*j)] = str[++(*i)];
		var[++(*j)] = 11;
		var[++(*j)] = str[++(*i)];
		i++;
		j++;
		while (str[*i] != '"')
			var[*j++] = str[*i++];
	}
	else if (str[*i] && (str[*i] == '<' && str[*i + 1] == '<') && (str[*i + 2] == '\''))
	{
		mini->do_not_exp = 1;
		var[*j] = 11;
		var[++(*j)] = str[*i];
		var[++(*j)] = str[++(*i)];
		var[++(*j)] = 11;
		var[++(*j)] = str[++(*i)];
		i++;
		j++;
		while (str[*i] != '\'')
			var[*j++] = str[*i++];
	}
	//////
	else if (((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32))
		str[*i] = 11;
	else if (str[*i] == '"')
	{
		if (((str[*i - 1] >= 9 && str[*i - 1] <= 13) || str[*i - 1] == 32))
			str[*i - 1] = 11;
		var[*j - 1] = str[*i - 1];
		var[*j] = str[*i];
		i++;
		j++;
		while (str[*i] != '"')
			var[*j++] = str[*i++];
	}
	else if (str[*i] == '\'')
	{
		if (((str[*i - 1] >= 9 && str[*i - 1] <= 13) || str[*i - 1] == 32))
			str[*i - 1] = 11;
		var[*j - 1] = str[*i - 1];
		var[*j] = str[*i];
		(*i)++;
		(*j)++;
		while (str[*i] != '\'')
			var[*j++] = str[*i++];
	}
	puts("---->");
	if ((str[*i] == '>' && str[*i + 1] == '>') || (str[*i] == '<' && str[*i + 1] == '<'))
	{
		if (str[*i] && (str[*i] == '<' && str[*i + 1] == '<'))
		{
			k = *i;
			k += 2;
			while (str[k] && ((str[k] >= 9 && str[k] <= 13) || str[k] == 32))
			{
				k++;
				if (str[k] && (str[k] == '"' || str[k] == '\''))
					mini->do_not_exp = 1;
			}
		}
		var[*j] = 11;
		var[++(*j)] = str[*i];
		var[++(*j)] = str[++(*i)];
		var[++(*j)] = 11;
	}
	else if ((str[*i] == '|' || str[*i] == '>' || str[*i] == '<' || (str[*i] == '>' && \
	str[*i + 1] == '>') || (str[*i] == '<' && str[*i + 1] == '<')))
	{
		var[*j] = 11;
		var[++(*j)] = str[*i];
		var[++(*j)] = 11;
	}
	else
		var[*j] = str[*i];
}

//puts a marker at the end of every string 
char	*prep(char	*str, t_minishell	*mini)
{
	char	*var;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	mini->do_not_exp = 0;
	var = malloc(sizeof(char) * (ft_strlen(str) + 20));
	while (str[i])
	{
		// prep_ext_1(mini, str, var, &i, &j);
		if (str[i] && (str[i] == '<' && str[i + 1] == '<') && (str[i + 2] == '"'))
		{
			mini->do_not_exp = 1;
			var[j] = 11;
			var[++j] = str[i];
			var[++j] = str[++i];
			var[++j] = 11;
			var[++j] = str[++i];
			i++;
			j++;
			while (str[i] != '"')
				var[j++] = str[i++];
		}
		else if (str[i] && (str[i] == '<' && str[i + 1] == '<') && (str[i + 2] == '\''))
		{
			mini->do_not_exp = 1;
			var[j] = 11;
			var[++j] = str[i];
			var[++j] = str[++i];
			var[++j] = 11;
			var[++j] = str[++i];
			i++;
			j++;
			while (str[i] != '\'')
				var[j++] = str[i++];
		}
		//////
		else if (((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
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
			if (str[i] && (str[i] == '<' && str[i + 1] == '<'))
			{
				k = i;
				k += 2;
				// printf("'%s'\n", str);
				// printf("'%c'\n", str[k]);
				while (str[k] && ((str[k] >= 9 && str[k] <= 13) || str[k] == 32))
				{
					k++;
					if (str[k] && (str[k] == '"' || str[k] == '\''))
						mini->do_not_exp = 1;
				}
			}
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
