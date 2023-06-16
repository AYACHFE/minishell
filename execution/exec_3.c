/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:14:55 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/16 20:15:30 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//search_for_ambig_redirections
int	check_ambig(char	*file, t_minishell	*mini)
{
	int	j;

	j = 2;
	if (check_ambig_ext(file, mini) == 1)
		return (1);
	if (mini->right_sp == 1)
	{
		while (file[j])
		{
			if (file[j] == 32 && (file[j + 1] != '\0'))
			{
				ft_putendl_fd("minishell: ambiguous redirect", 2);
				return (1);
			}
			j++;
		}
	}
	return (0);
}

int	check_ambig_ext(char	*file, t_minishell	*mini)
{
	int	j;

	j = 2;
	if (mini->center_sp == 1 || mini->just_sp == 1)
	{
		ft_putendl_fd("minishell: ambiguous redirect", 2);
		return (1);
	}
	if (mini->left_sp == 1)
	{
		while (file[j])
		{
			if (file[j] == 32 && (file[j - 1] != 32 && file[j - 1] != '>' \
			&& file[j - 2] != '>'))
			{
				ft_putendl_fd("minishell: ambiguous redirect", 2);
				return (1);
			}
			j++;
		}
	}
	return (0);
}
