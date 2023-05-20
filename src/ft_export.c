/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:38:50 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/20 18:56:24 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_export(t_minishell *mini)
{
	if (mini->count_str > 1)
	{
		ft_rem_var(mini->str ,mini);
		ft_rem_var_export(mini->str ,mini);
		// ft_add_declare_in_pos(mini);
	}
	else
		print_export(mini);
	
}

void	ft_rem_var(char **str, t_minishell *mini)
{
	int i;
	int j;
	int d;
	int n;
	char **my_tmp;

	j = 0;
	n = 0;
	while (mini->my_env[j])
		j++;
	my_tmp = malloc(sizeof(char *) * (j + mini->count_str)); 
	d = 0;
	j = 0;
	while (mini->my_env[d])
	{
		my_tmp[n] = ft_strdup(mini->my_env[d]);
		n++;
		d++;
	}
	i = 1;
	while(str[i] && (ft_strchr(mini->str[i], '=') != NULL))
	{
		my_tmp[n] = ft_strdup(mini->str[i]);
		n++;
		i++;
	}	
	my_tmp[n] = NULL; 
	i = 0;
	while (mini->my_env[i]) 
	{
		free(mini->my_env[i]);
		i++;
	}
	mini->my_env = my_tmp;
}

void	ft_rem_var_export(char **str, t_minishell *mini)
{
	int i;
	int j;
	int d;
	int n;
	char **my_tmp;

	j = 0;
	n = 0;
	while (mini->my_export[j])
		j++;
	my_tmp = malloc(sizeof(char *) * (j + mini->count_str)); 
	d = 0;
	j = 0;
	while (mini->my_export[d])
	{
		my_tmp[n] = ft_strdup(mini->my_export[d]);
		n++;
		d++;
	}
	i = 1;
	while(str[i])
	{
		my_tmp[n] = ft_strdup(mini->str[i]);
		n++;
		i++;
	}	
	my_tmp[n] = NULL; 
	i = 0;
	while (mini->my_export[i]) 
	{
		free(mini->my_export[i]);
		i++;
	}
	mini->my_export = my_tmp;
}

void	print_export(t_minishell *mini)
{
	int	j;

	j = 0;
	while(mini->my_export[j])
	{
		printf("%s\n", mini->my_export[j]);
		j++;
	}
}

// void	env_to_export(t_minishell	*mini)
// {
// 	int	i;
// 	char s[12] ="declare -x ";

// 	i = 0;
// 	while (mini->my_env[i])
// 	{
// 		free(mini->my_export[i]);
// 		i++;
// 	}
// 	free(mini->my_export);
	
// }
