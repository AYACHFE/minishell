/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:03:56 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/19 11:04:24 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_declare(t_minishell *mini)
{
	int		i;
	int		j;
	char	*s;

	s = "declare -x ";
	j = 0;
	i = 0;
	ft_tmp_my_env(mini);
	while (mini->tmp_my_env[i])
		i++;
	mini->my_export = malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		mini->my_export[j] = ft_strjoin(s, mini->tmp_my_env[j]);
		j++;
	}
	mini->my_export[j] = NULL;
}

void	ft_tmp_my_env_pos(t_minishell *mini, int pos)
{
	int	i;
	int	j;
	int	d;

	i = 0;
	j = 0;
	mini->tmp_my_env = malloc(sizeof(char *) * (pos + 1));
	j = 0;
	while (mini->my_export[pos][j])
		j++;
	mini->tmp_my_env[pos] = malloc(j + 3);
	j = 0;
	d = 0;
	while (mini->my_export[pos][j])
	{
		mini->tmp_my_env[pos][d] = mini->my_export[pos][j];
		if (mini->my_export[pos][j] == '=' || \
		mini->my_export[pos][j + 1] == '\0')
			mini->tmp_my_env[pos][++d] = '"';
		d++;
		j++;
	}
	mini->tmp_my_env[pos][d] = '\0';
	mini->tmp_my_env[pos + 1] = NULL;
}
