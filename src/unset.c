/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:31:45 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/19 15:33:05 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rem_var(t_minishell	*mini, int pos)
{
	int		i;

	i = 0;
	free(mini->my_env[pos]);
	while (mini->my_env[pos])
	{
		mini->my_env[pos] = mini->my_env[pos + 1];
		pos++;
	}
	mini->my_env[pos] = NULL;
}

void	search_in_env(t_minishell	*mini, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (mini->my_env[i])
	{
		if (ft_strncmp(mini->my_env[i], str, ft_cnt(mini->my_env[i])) == 0)
			rem_var(mini, i);
		i++;
	}
}

void ft_unset(t_minishell *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (mini->str[j])
	{
		while (mini->str[j])
		{
			search_in_env(mini, mini->str[j]);
			j++;
		}
	}
}