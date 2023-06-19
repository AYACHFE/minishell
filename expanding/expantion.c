/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:18:58 by rarraji           #+#    #+#             */
/*   Updated: 2023/06/19 10:39:20 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key(char *str)
{
	char	*s;
	int		n;

	n = 0;
	if (str[n] == '$')
		return (ft_strdup("$"));
	n = 0;
	if ((ft_strchr("@", *str) || !ft_isalpha(*str)) && *str != '_')
		return (ft_substr(str, 0, 1));
	if (str[n] == '?')
		s = ft_substr(str, n, 2);
	else
	{
		while (str[n] && str[n] != '\"' && str[n] != '\'' \
		&& str[n] != '$' && str[n] != '-')
			n++;
	}
	return (ft_substr(str, 0, n));
}

char	*get_value_2(t_minishell *mini, char *str, int i)
{
	int	d;

	while (mini->my_env[++i])
	{
		d = 0;
		mini->max = ft_cnt(mini->my_env[i]);
		if (ft_cnt(mini->my_env[i]) < ft_cnt(str))
			mini->max = ft_cnt(str);
		if (ft_strncmp(mini->my_env[i], str, mini->max) == 0)
		{
			while (mini->my_env[i][d])
			{
				if (mini->my_env[i][d] == '=')
				{
					mini->ambg = i;
					return (ft_substr(mini->my_env[i], d + 1, \
					ft_strlen(mini->my_env[i])));
				}
				else
					d++;
			}
		}
	}
	return (NULL);
}

char	*get_value(char *str, t_minishell *mini)
{
	int		i;
	char 	*value;

	i = -1;
	value = get_value_2(mini, str, 0);
	if (str[0] == '?')
		return (ft_itoa(mini->exit_code));
	else if (str[0] == '$')
		return (ft_strdup(""));
	if (value != NULL)
		return (value);
	return (NULL);
}

int	get_len(char *s, t_minishell *mini, int len)
{
	int		i;
	char	*value;
	char	*key;
	int		dq;

	i = 0;
	dq = 0;
	while (s[i])
	{
		if (s[i] == '$' && ((s[i + 1] && dq == 0) || \
		(s[i + 1] != '"' && dq == 1)))
		{
			key = get_key(&s[++i]);
			value = get_value(key, mini);
			len += ft_strlen(value);
			i += ft_strlen(key);
			free(key);
			free(value);
		}
		if (s[i++] == '"')
			dq = !dq;
		len++;
	}
	return (len);
}

void	ft_check_dollar1(t_minishell *mini)
{
	int		len;
	t_prep	prep;

	prep.n = 0;
	mini->no_exp = 0;
	mini->ambg = -1;
	mini->tmp_cmd = malloc(sizeof(char *) * (mini->cmd_nb + 1));
	while (mini->cmd[prep.n])
	{
		len = get_len(mini->cmd[prep.n], mini, 0);
		mini->tmp_cmd[prep.n] = ft_calloc(len + 1, 1);
		ft_expand(&prep, mini->cmd[prep.n], mini);
		prep.n++;
	}
	mini->tmp_cmd[prep.n] = NULL;
}
