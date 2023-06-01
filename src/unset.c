/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:42:40 by rarraji           #+#    #+#             */
/*   Updated: 2023/06/01 09:05:56 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rem_var_env(t_minishell	*mini, int pos)
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
			rem_var_env(mini, i);
		i++;
	}
}

void	rem_var_export(t_minishell	*mini, int pos)
{
	int		i;

	i = 0;
	
	free(mini->my_export[pos]);
	while (mini->my_export[pos])
	{
		mini->my_export[pos] = mini->my_export[pos + 1];
		pos++;
	}
	mini->my_export[pos] = NULL;
}

void	search_in_export(t_minishell	*mini, char *str)
{
	char	*sub;
	int		i;

	i = 0;
	while (mini->my_export[i])
	{
		sub = ft_substr(mini->my_export[i], 11, ft_strlen(mini->my_export[i]));
		if (ft_strncmp(sub, str, ft_cnt(sub)) == 0)
		{
			rem_var_export(mini, i);
		}
		i++;
	}
}

void ft_unset(t_minishell *mini)
{
	int	j;

	j = 1;
	if (mini->str[j])
	{
		while (mini->str[j])
		{
			search_in_env(mini, mini->str[j]);
			j++;
		}
		j = 0;
		while (mini->str[j])
		{
			search_in_export(mini, mini->str[j]);
			j++;
		}
	}
}
