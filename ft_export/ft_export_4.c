/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:32:42 by rarraji           #+#    #+#             */
/*   Updated: 2023/06/18 20:49:35 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_double_ext_1(char	*s, char	*str, int	*i, int	*tmp)
{
	int	j;

	j = 0;
	while (s[j])
	{
		str[*i] = s[j];
		if((ft_strchr(s, '=') != NULL) && (s[j] == '=' && s[j + 1] == '\0') && *tmp == 0)
		{
			str[++(*i)] = '"';
			str[++(*i)] = '"';
			return ;
		}
		else if (ft_strchr(s, '=') != NULL && s[j] == '=' && *tmp == 0)
		{
			str[++(*i)] = '"';		
			*tmp = 1;
		}
		(*i)++;
		j++;
	}
	if(s[j] == '\0' && ft_strchr(s, '=') != NULL)
		str[(*i)] = '"';
	str[++(*i)] = '\0';
}

char *ft_add_double(char *s)
{
	char	dec[12] ="declare -x ";
	char	*str;
	int		i;
	int		j;
	int		tmp;

	tmp = 0;
	i = 0;
	j = 0;
	while(s[i])
		i++;
	str = malloc(i + 14);
	if (!str)
		return (0);
	i = 0;
	while(dec[i])
	{
		str[i] = dec[i];
		i++;
	}
	ft_add_double_ext_1(s, str, &i, &tmp);
	free(s);
	return (str);
}

void	add_var_export_pr2(char	**str, char	**my_tmp, int	*n)
{
	int	i;

	i = 0;
	while(str[i])
	{

		if(check_valid_exp(str[i], 0) == 0)
			i++;
		else
		{
			my_tmp[*n] = ft_strdup1(str[i]);
			my_tmp[*n] = ft_add_double(my_tmp[*n]);
			(*n)++;
			i++;
		}
	}
	my_tmp[*n] = NULL;
}

void	add_var_export_pr1(t_minishell	*mini, char	**str, char	**my_tmp, int	*n)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (str[i])
	{
		if(chec_var_env_exp(str[i], mini, 0) != 0)
			search_in_export(mini, str[i]);
		i++;
	}
	while (mini->my_export[d])
	{
		my_tmp[*n] = ft_strdup(mini->my_export[d]);
		(*n)++;
		d++;
	}
}

void	add_var_export(char **str, t_minishell *mini, int t)
{
	char **my_tmp;
	int	j;
	int n;

	n = 0;
	j = 0;
	while (mini->my_export[j])
		j++;
	my_tmp = malloc(sizeof(char *) * (j + t + 1));
	add_var_export_pr1(mini, str, my_tmp, &n);
	add_var_export_pr2(str, my_tmp, &n);
	j = 0;
	while (mini->my_export[j]) 
		free(mini->my_export[j++]);
	free(mini->my_export);
	mini->my_export = my_tmp;

}