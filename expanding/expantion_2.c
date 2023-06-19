/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:25:24 by rarraji           #+#    #+#             */
/*   Updated: 2023/06/19 10:23:58 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_var(char *s, char *d, t_prep	*prep, t_minishell *mini)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	key = get_key(s);
	value = get_value(key, mini);
	if (value && mini->ambg != -1)
	{
		ft_check_sp(mini->my_env[mini->ambg], mini);
		if (ft_strncmp(value, ">", 2) == 0 || \
			ft_strncmp(value, ">>", 3) == 0 || \
			ft_strncmp(value, "<", 2) == 0 || \
			ft_strncmp(value, "<<", 3) == 0)
			mini->no_exp = 1;
	}
	while (value && value[i])
	{
		d[prep->j] = value[i];
		prep->j++;
		i++;
	}
	d[prep->j] = '\0';
	i = ft_strlen(key);
	free(key);
	free(value);
	return (i);
}



void handle_double_1(char *s, t_minishell *mini, t_prep	*prep, int *k)
{
	int			d;
	char		*key;
	char		*value;

	d = 0;
	(*k)++;
	key = get_key(&s[*k]);
	value = get_value(key, mini);
	while (value && value[d])
	{
		mini->tmp_cmd[prep->n][prep->j] = value[d];
		prep->j++;
		d++;
	}
	prep->i += ft_strlen(key);
	*k += ft_strlen(key);
	free(key);
	free(value);
}

void	handle_double(char *s, t_minishell *mini, t_prep	*prep)
{
	int		k;

	k = 0;
	while (s[k] != '"' && s[k])
	{
		if (s[k] == '$' && s[k + 1] != '"')
			handle_double_1(s, mini, prep, &k);
		else
		{
			mini->tmp_cmd[prep->n][prep->j] = s[k];
			prep->j++;
			k++;
		}
	}
	mini->tmp_cmd[prep->n][prep->j] = '\0';
	k++;
	prep->i += k;
}

void	handle_single(char *s, t_minishell *mini, t_prep	*prep)
{
	if (mini->deuble == 0)
		prep->i++;
	while (s[prep->i] != '\'' && s[prep->i])
	{
		mini->tmp_cmd[prep->n][prep->j] = s[prep->i];
			prep->i++;
			prep->j++;
	}
	if (s[prep->i] == '\'')
		(prep->i)++;
}

void	ft_expand(t_prep	*prep, char *s, t_minishell *mini)
{
	mini->deuble = 0;
	prep->i = 0;
	prep->j = 0;
	while (s[prep->i])
	{
		if (s[prep->i] == '$' && s[prep->i + 1])
		{
			prep->i++;
			prep->i += expand_var(&s[prep->i], mini->tmp_cmd[prep->n], prep, mini);
		}
		else if (s[prep->i] == '"')
		{
			prep->i++;
			handle_double(&s[prep->i], mini, prep);
		}
		else if (s[prep->i] == '\'' && mini->deuble == 0)
			handle_single(&(s[prep->i]), mini, prep);
		else
			mini->tmp_cmd[prep->n][prep->j++] = s[prep->i++];
	}
	mini->tmp_cmd[prep->n][prep->j] = '\0';
}

void	ft_check_sp(char *s, t_minishell *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	mini->left_sp = 0;
	mini->right_sp = 0;
	mini->center_sp = 0;
	mini->just_sp = 0;
	while (s[i])
	{
		if (s[i] == '=' && s[i + 1] == '\0')
		{
			mini->just_sp = 1;
			return ;
		}
		if (s[i] == '=' && s[i + 1] == 32)
		{
			j = i;
			j++;
			while (s[j] && s[j] == 32)
				j++;
			if (s[j + 1] == '\0')
			{
				mini->just_sp = 1;
				return ;
			}
		}
		if (s[i] == '=' && s[i + 1] == 32)
		{
			mini->left_sp = 1;
			return ;
		}
		else if (s[i] == 32)
		{
			j = i;
			while (s[j] && s[j] == 32)
				j++;
			if (s[j] == '\0')
			{
				mini->right_sp = 1;
				return ;
			}
			else if (s[i] != '\0')
			{
				mini->center_sp = 1;
				return ;
			}
		}
		i++;
	}
}

