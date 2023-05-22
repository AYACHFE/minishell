/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:41:45 by rarraji           #+#    #+#             */
/*   Updated: 2023/05/22 14:35:52 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_export(t_minishell *mini)
{
	if (mini->count_str > 1)
	{
		ft_rem_var(mini->str ,mini);
		ft_rem_var_export(mini->str ,mini);
	}
	else
		print_export(mini);
	
}

int	ft_check_var_exect(char *s,t_minishell *mini, int var)
{
	int i;
	int	j;
	i = 0;
	// d = 0;
	j=0;
	if (var == 0)
	{	
		while (mini->my_export[i])
		{
			// i = tmp;
			while (mini->my_export[i][j] == s[j] && s[j] != '=')
				j++;
			if(mini->my_export[i][j] == '=' && s[j] == '=')
				return (i);
			else
				j = 0;	
			i++;
		}
	}
	else
	{
		while (mini->my_env[i])
		{
			// i = tmp;
			while (mini->my_env[i][j] == s[j] && s[j] != '=')
				j++;
			if(mini->my_env[i][j] == '=' && s[j] == '=')
				return (i);
			else
				j = 0;	
			i++;
		}
	}
	return (0);
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
	i = 0;
	while (str[i])
	{
		if (ft_check_var_exect(str[i], mini, 0) != 0)
			rem_var_env(mini, ft_check_var_exect(str[i], mini, 1));
		i++;
	}
	while (mini->my_env[d])
	{
		my_tmp[n] = ft_strdup(mini->my_env[d]);
		n++;
		d++;
	}
	i = 1;
	while(str[i] && (ft_strchr(mini->str[i], '=') != NULL))
	{
		if(ft_check_var_exect(str[i], mini, 0) != 0)
			ft_unset(mini);
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

void	ft_rem_var_export(char **str, t_minishell *mini) // add_variable
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
