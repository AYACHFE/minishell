/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:18:58 by rarraji           #+#    #+#             */
/*   Updated: 2023/06/18 18:16:08 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_check_sp(char *s, t_minishell *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	mini->left_sp = 0;
	mini->right_sp = 0;
	mini->center_sp = 0;
	mini->just_sp = 0;
	while(s[i])
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


/////////////////////////



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
		while (str[n] && str[n] != '\"' && str[n] != '\'' && str[n] != '$' && str[n] != '-')
			n++;
	}
	return (ft_substr(str, 0, n));
}

char *get_value_2(t_minishell *mini, char *str, int i)
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
	return(NULL);
}


char	*get_value(char *str, t_minishell *mini)
{
	int	i;

	i = -1;
	if (str[0] == '?')
		return (ft_itoa(mini->exit_code));
	else if (str[0] == '$')
		return (ft_strdup(""));
	if(get_value_2(mini, str, 0) != NULL)
		return(get_value_2(mini, str, 0));
	return NULL;
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
		if (s[i] == '$' && ((s[i + 1] && dq == 0) || (s[i + 1] != '"' && dq == 1)))
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

int	expand_var(char *s, char *d, int *j, t_minishell *mini)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	key = get_key(s);
	value = get_value(key, mini);
	if(value && mini->ambg != -1)
	{
		ft_check_sp(mini->my_env[mini->ambg], mini);
		if(ft_strncmp(value, ">", 2) == 0 || ft_strncmp(value, ">>", 3) == 0 || ft_strncmp(value, "<", 2) == 0 || ft_strncmp(value, "<<", 3) == 0)
			mini->no_exp = 1;
	}
	while (value && value[i])
	{
		d[*j] = value[i];
		(*j)++;
		i++;
	}
	d[*j] = '\0';
	return (ft_strlen(key));
}

void handle_double(char *s, int *i, int *j, t_minishell *mini, int *n)
{
	char	*key;
	char 	*value;	
	int		d;
	int		k;
	
	k = 0;
	while (s[k] != '"' && s[k])
	{
		if (s[k] == '$' && s[k + 1] != '"')
		{
			k++;
			d = 0;
			key = get_key(&s[k]);
			value = get_value(key, mini);
			while (value && value[d])
			{
				mini->tmp_cmd[*n][*j] = value[d];
				(*j)++;
				d++;
			}
			*i += ft_strlen(key);
			k += ft_strlen(key);
		}
		else
		{
			mini->tmp_cmd[*n][*j] = s[k];
			(*j)++;
			k++;
		}
	}
	mini->tmp_cmd[*n][*j] = '\0';
	k++;
	*i += k;
}

void	handle_single(char *s, int *i, int *j, t_minishell *mini, int *n)
{
	if (mini->deuble == 0)
		(*i)++;
	while (s[*i] != '\'' && s[*i])
	{
		mini->tmp_cmd[*n][*j] = s[*i];
			(*i)++;
			(*j)++;
	}
	if (s[*i] == '\'')
		(*i)++;
}

void	ft_expand(int n, char *s, t_minishell *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	mini->deuble = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1])
		{
			i++;
			i += expand_var(&s[i], mini->tmp_cmd[n], &j, mini);
		}
		else if (s[i] == '"')
		{
			i++;
			handle_double(&s[i], &i, &j, mini, &n);
		}
		else if (s[i] == '\'' && mini->deuble == 0)
			handle_single(&(s[i]), &i, &j, mini, &n);
		else
			mini->tmp_cmd[n][j++] = s[i++];
	}
	mini->tmp_cmd[n][j] = '\0';
}

void	ft_check_dollar1(t_minishell *mini)
{
	int	len;
	int	i;

	i = 0;
	mini->no_exp = 0;
	mini->ambg = -1;
	mini->tmp_cmd = malloc(sizeof(char *) * (mini->cmd_nb + 1));
	while (mini->cmd[i])
	{
			len = get_len(mini->cmd[i], mini, 0);
			mini->tmp_cmd[i] = ft_calloc(len + 1, 1);
			ft_expand(i, mini->cmd[i], mini);
			i++;
	}
	mini->tmp_cmd[i] = NULL;
}
