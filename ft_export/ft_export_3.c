/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:32:40 by rarraji           #+#    #+#             */
/*   Updated: 2023/06/18 20:53:46 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env(t_minishell	*mini, char	**str, char	**my_tmp)
{
	int	i;
	int	j;
	int	d;

	i = -1;
	j = 0;
	d = 0;
	while (str[++i])
	{
		if (chec_var_env_exp(str[i], mini, 0) != 0)
			rem_var_env(mini, chec_var_env_exp(str[i], mini, 1));
	}
	while (mini->my_env[d])
		my_tmp[j++] = ft_strdup(mini->my_env[d++]);
	d = j;
	i = 0;
	j = 0;
	while(str[i] && (ft_strchr(str[i], '=') != NULL))
	{
		if(check_valid_exp(str[i], 0) == 0)
			i++;
		else
			my_tmp[d++] = ft_strdup1(str[i++]);
	}
	my_tmp[d] = NULL;
}

void	add_var_env(char **str, t_minishell *mini, int	t)
{
	char **my_tmp;
	int i;
	int j;

	i = 0;
	j = 0;
	while (mini->my_env[j])
		j++;	
	my_tmp = malloc(sizeof(char *) * (j + t + 1)); 
	add_env(mini, str, my_tmp);
	i = 0;
	while (mini->my_env[i]) 
	{
		free(mini->my_env[i]);
		i++;
	}
	free(mini->my_env);
	mini->my_env = my_tmp;
}