/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:59:12 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/18 18:16:08 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//puts a marker at the end of every string 
char	*prep(char	*str, t_minishell	*mini)
{
	t_prep	prep;

	prep.i = 0;
	prep.j = 0;
	mini->do_not_exp = 0;
	prep.var = malloc(sizeof(char) * (ft_strlen(str) + 20));
	while (str[prep.i])
	{
		prep_ext_1(mini, &prep, str);
		prep.i++;
		prep.j++;
		prep.var[prep.j] = '\0';
	}
	return (prep.var);
}

void	prep_ext_1(t_minishell	*mini, t_prep	*prep, char	*str)
{
	if (str[prep->i] && (str[prep->i] == '<' && str[prep->i + 1] \
	== '<') && (str[prep->i + 2] == '"'))
		prep_ext_2(mini, prep, str);
	else if (str[prep->i] && (str[prep->i] == '<' && str[prep->i + 1] \
	== '<') && (str[prep->i + 2] == '\''))
		prep_ext_3(mini, prep, str);
	else if (((str[prep->i] >= 9 && str[prep->i] <= 13) || str[prep->i] == 32))
		str[prep->i] = 11;
	else if (str[prep->i] == '"' && prep->i)
		prep_ext_4(prep, str);
	else if (str[prep->i] == '\'')
		prep_ext_5(prep, str);
	if ((str[prep->i] == '>' && str[prep->i + 1] == '>') || (str[prep->i] \
	== '<' && str[prep->i + 1] == '<'))
		prep_ext_6(mini, prep, str);
	else if ((str[prep->i] == '|' || str[prep->i] == '>' || str[prep->i] == \
	'<' || (str[prep->i] == '>' && str[prep->i + 1] == '>') || (str[prep->i] \
	== '<' && str[prep->i + 1] == '<')))
	{
		prep->var[prep->j] = 11;
		prep->var[++prep->j] = str[prep->i];
		prep->var[++prep->j] = 11;
	}
	else
		prep->var[prep->j] = str[prep->i];
}

void	prep_ext_2(t_minishell	*mini, t_prep	*prep, char	*str)
{
	mini->do_not_exp = 1;
	prep->var[prep->j] = 11;
	prep->var[++prep->j] = str[prep->i];
	prep->var[++prep->j] = str[++prep->i];
	prep->var[++prep->j] = 11;
	prep->var[++prep->j] = str[++prep->i];
	prep->i++;
	prep->j++;
	while (str[prep->i] != '"')
		prep->var[prep->j++] = str[prep->i++];
}

void	prep_ext_3(t_minishell	*mini, t_prep	*prep, char	*str)
{
	mini->do_not_exp = 1;
	prep->var[prep->j] = 11;
	prep->var[++prep->j] = str[prep->i];
	prep->var[++prep->j] = str[++prep->i];
	prep->var[++prep->j] = 11;
	prep->var[++prep->j] = str[++prep->i];
	prep->i++;
	prep->j++;
	while (str[prep->i] != '\'')
		prep->var[prep->j++] = str[prep->i++];
}

void	prep_ext_4(t_prep	*prep, char	*str)
{
	if (str[prep->i] && ((str[prep->i - 1] >= 9 && str[prep->i - 1] <= 13) || \
	str[prep->i - 1] == 32))
		str[prep->i - 1] = 11;
	prep->var[prep->j - 1] = str[prep->i - 1];
	prep->var[prep->j] = str[prep->i];
	prep->i++;
	prep->j++;
	while (str[prep->i] && str[prep->i] != '"')
	{
		prep->var[prep->j++] = str[prep->i++];
	}
}
