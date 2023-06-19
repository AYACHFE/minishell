/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:09:51 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/19 11:17:58 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_sp_1(char	*s, t_minishell	*mini, int	*j, int i)
{
	if (s[i] == '=' && s[i + 1] == '\0')
	{
		mini->just_sp = 1;
		return ;
	}
	if (s[i] == '=' && s[i + 1] == 32)
	{
		*j = i;
		(*j)++;
		while (s[*j] && s[*j] == 32)
			(*j)++;
		if (s[*j + 1] == '\0')
		{
			mini->just_sp = 1;
			return ;
		}
	}
}

void	ft_check_sp_2(char	*s, t_minishell	*mini, int	*j, int i)
{
	if (s[i] == '=' && s[i + 1] == 32)
	{
		mini->left_sp = 1;
		return ;
	}
	else if (s[i] == 32)
	{
		*j = i;
		while (s[*j] && s[*j] == 32)
			(*j)++;
		if (s[*j] == '\0')
		{
			mini->right_sp = 1;
			return ;
		}
		else if (s[i] != '\0')
		{
			mini->center_sp = 1;
			return ;
		}
	}
}

void	ft_check_sp(char *s, t_minishell *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	mini->left_sp = 0;
	mini->right_sp = 0;
	mini->center_sp = 0;
	mini->just_sp = 0;
	while (s[i])
	{
		ft_check_sp_1(s, mini, &j, i);
		ft_check_sp_2(s, mini, &j, i);
		i++;
	}
}
