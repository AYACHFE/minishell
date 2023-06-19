/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:41:45 by rarraji           #+#    #+#             */
/*   Updated: 2023/06/18 19:31:58 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup1(char *s1)
{
	char	*ss1;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (s1[++i])
	{
		if (s1[i] == '\"')
			j++;
	}
	ss1 = malloc(((i - j) + 1) * (sizeof(char)));
	if (!ss1)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		if (s1[i] == '\"')
			i++;
		else
			ss1[j++] = s1[i++];
	}
	ss1[j] = '\0';
	return (ss1);
}

int	check_valid_exp(char *arg, int check)
{
	int	i;

	i = 0;
	while (arg[i] != '=' && arg[i])
	{
		if (ft_isdigit(arg[0]) == 1)
		{
			if (check == 1)
				ft_putendl_fd("minishell: not a valid identifier", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	export_check(t_minishell	*mini, char	*s)
{
	int	i;
	int	j;
	int	d;

	i = 0;
	j = 0;
	d = 11;
	while (mini->my_export[i])
	{
		while (mini->my_export[i][d] == s[j] && s[j] != '=' \
		&& mini->my_export[i][d] && s[j])
		{
			j++;
			d++;
		}
		if ((mini->my_export[i][d] == '=' || mini->my_export[i][d] == '\0') && \
			(s[j] == '=' || s[j] == '\0'))
			return (i);
		else
		{
			d = 11;
			j = 0;
		}
		i++;
	}
	return (0);
}

int	chec_var_env_exp(char *s, t_minishell *mini, int var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (var == 0)
	{
		if (export_check(mini, s) != 0)
			return (export_check(mini, s));
	}
	else
	{
		while (mini->my_env[i])
		{
			while (mini->my_env[i][j] == s[j] && s[j] != '=')
				j++;
			if (mini->my_env[i][j] == '=' && s[j] == '=')
				return (i);
			else
				j = 0;
			i++;
		}
	}
	return (0);
}

void	print_export(t_minishell *mini)
{
	int	j;

	j = 0;
	while (mini->my_export[j])
	{
		printf("%s\n", mini->my_export[j]);
		j++;
	}
}
