/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:43:22 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/19 10:44:24 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_single_heredoc(char *s, t_minishell *mini, \
t_prep	*prep, char	**res)
{
	if (mini->deuble == 0)
		prep->i++;
	while (s[prep->i] != '\'' && s[prep->i])
	{
		res[prep->n][prep->j] = s[prep->i];
		prep->i++;
		prep->j++;
	}
	if (s[prep->i] == '\'')
		(prep->i)++;
}

void	handle_double_heredoc(char *s, t_minishell *mini, \
t_prep	*prep, char	**res)
{
	int		k;

	k = 0;
	while (s[k] != '"' && s[k])
	{
		if (s[k] == '$' && s[k + 1] != '"')
			handle_double_1(s, mini, prep, &k);
		else
		{
			res[prep->n][prep->j] = s[k];
			prep->j++;
			k++;
		}
	}
	res[prep->n][prep->j] = '\0';
	k++;
	prep->i += k;
}

void	ft_expand_heredoc(t_prep	*prep, char *s, \
t_minishell *mini, char	**res)
{
	mini->deuble = 0;
	prep->i = 0;
	prep->j = 0;
	while (s[prep->i])
	{
		if (s[prep->i] == '$' && s[prep->i + 1])
		{
			prep->i++;
			prep->i += expand_var(&s[prep->i], res[prep->n], prep, mini);
		}
		else if (s[prep->i] == '"')
		{
			prep->i++;
			handle_double_heredoc(&s[prep->i], mini, prep, res);
		}
		else if (s[prep->i] == '\'' && mini->deuble == 0)
			handle_single_heredoc(&(s[prep->i]), mini, prep, res);
		else
			res[prep->n][prep->j++] = s[prep->i++];
	}
	res[prep->n][prep->j] = '\0';
}

void	ft_check_dollar_heredoc(t_minishell *mini, char	*var, char	**res)
{
	char	**str;
	int		len;
	t_prep	prep;

	prep.n = 0;
	str = ft_split(var, 32);
	mini->no_exp = 0;
	mini->ambg = -1;
	while (str[prep.n])
	{
		len = get_len(str[prep.n], mini, 0);
		res[prep.n] = ft_calloc(len + 1, 1);
		ft_expand_heredoc(&prep, str[prep.n], mini, res);
		prep.n++;
	}
	res[prep.n] = NULL;
}
