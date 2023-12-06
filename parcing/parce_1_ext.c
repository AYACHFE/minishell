/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_1_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:36:06 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/17 12:29:45 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prep_ext_5(t_prep	*prep, char	*str)
{
	if (((str[prep->i - 1] >= 9 && str[prep->i - 1] <= 13) || \
	str[prep->i - 1] == 32))
		str[prep->i - 1] = 11;
	prep->var[prep->j - 1] = str[prep->i - 1];
	prep->var[prep->j] = str[prep->i];
	prep->i++;
	prep->j++;
	while (str[prep->i] != '\'')
		prep->var[prep->j++] = str[prep->i++];
}

void	prep_ext_6(t_minishell	*mini, t_prep	*prep, char	*str)
{
	int	k;

	k = 0;
	if (str[prep->i] && (str[prep->i] == '<' && str[prep->i + 1] == '<'))
	{
		k = prep->i;
		k += 2;
		while (str[k] && ((str[k] >= 9 && str[k] <= 13) || str[k] == 32))
		{
			k++;
			if (str[k] && (str[k] == '"' || str[k] == '\''))
				mini->do_not_exp = 1;
		}
	}
	prep->var[prep->j] = 11;
	prep->var[++prep->j] = str[prep->i];
	prep->var[++prep->j] = str[++prep->i];
	prep->var[++prep->j] = 11;
}
