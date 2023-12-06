/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:02:17 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/19 11:06:38 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cnt(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0' && str[i] != '\"' \
	&& str[i] && str[i] != '-' && str[i] != '@' && str[i] != '$')
		i++;
	return (i);
}

void	ft_tmp_my_env_3(t_minishell	*mini, int *i, int *d, int *j)
{
	if (mini->my_env[*i][*j] == '$' || mini->my_env[*i][*j] == '\"')
	{
		mini->tmp_my_env[*i][*d] = '\\';
		mini->tmp_my_env[*i][++(*d)] = mini->my_env[*i][*j];
	}
	else
		mini->tmp_my_env[*i][*d] = mini->my_env[*i][*j];
	(*d)++;
	(*j)++;
	if (mini->my_env[*i][*j] == '\0')
		mini->tmp_my_env[*i][*d] = '\"';
}

void	ft_tmp_my_env_2(t_minishell	*mini, int *i, int *d, int *j)
{
	while (mini->my_env[*i][*j])
	{
		if (mini->my_env[*i][*j] == '=' && mini->my_env[*i][*j] != '\0')
		{
			mini->tmp_my_env[*i][*d] = mini->my_env[*i][*j];
			mini->tmp_my_env[*i][++(*d)] = '\"';
			(*d)++;
			(*j)++;
			while (mini->my_env[*i][*j] != '\0')
				ft_tmp_my_env_3(mini, i, d, j);
			if (mini->my_env[*i][*j] == '\0')
			{
				mini->tmp_my_env[*i][*d] = '\"';
				return ;
			}
		}
		else
			mini->tmp_my_env[*i][*d] = mini->my_env[*i][*j];
		(*d)++;
		(*j)++;
	}
}

void	ft_tmp_my_env_1(t_minishell	*mini)
{
	int	i;
	int	j;
	int	d;

	i = 0;
	while (mini->my_env[i])
	{
		j = 0;
		while (mini->my_env[i][j])
			j++;
		mini->tmp_my_env[i] = malloc(j + 4);
		j = 0;
		d = 0;
		ft_tmp_my_env_2(mini, &i, &d, &j);
		mini->tmp_my_env[i][++d] = '\0';
		i++;
	}
	mini->tmp_my_env[i] = NULL;
}

void	ft_tmp_my_env(t_minishell *mini)
{
	int	i;

	i = 0;
	while (mini->my_env[i])
		i++;
	mini->tmp_my_env = malloc(sizeof(char *) * (i + 1));
	ft_tmp_my_env_1(mini);
}
