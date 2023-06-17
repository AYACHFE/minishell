/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:43:22 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/17 22:10:32 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_check_dollar_heredoc(t_minishell *mini, char	*var, char	**res)
{
	int i;
	int j;
	int d;
	int tmp;
	int single;
	int deuble;
	int k;
	int	s;
	char	**str;

	k = 0;
	
	i = 0;
	j = 0;
	d = 0;
	s = 0;
	single = 0;
	tmp = 0;
	deuble = 0;
	str = ft_split(var, 32);
	while (str[i])
	{
		d = 0;
		while(str[i][s])
		{
			if(str[i][s] == '$')
			{
				s++;
			}
			else
			  break;     
		}
		if(str[i][s] == '\0')
		{
			res[j] = ft_strdup("$");
			j++;
		}

		if (str[i][d] == '\'')
		{
			d++;
			single = 1;
		}
		if (str[i][d] == '\"' && single != 1)
		{
			deuble =1;
			d++;
		}
		while(str[i][d] && single != 1 )
		{
			if (str[i][d] == '$')
				tmp++;
			d++;    
		}
		if (tmp > 0 && str[i][s] != '\0')
		{
			res[j] = ft_change_var(str[i], mini, tmp);
			j++;
		}
		else if (str[i][s] != '\0')
		{
			if (deuble == 0 && single != 1)
			{
				res[j] = ft_substr(str[i], 0, ft_strlen(str[i]));
				j++;
			}
			else
			{
				k = 0;
				if (deuble == 1 && str[i][k + 1] == '\"' && str[i][k + 2] == '\0')
					break;      
				res[j] = ft_substr1(str[i], k, ft_hsb(str[i]));
				j++;    
			}
				
		}
		s = 0;
		tmp = 0;
		i++;
	}
	res[j] = NULL;
}
