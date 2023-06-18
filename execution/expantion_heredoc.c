/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:43:22 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/18 15:05:00 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expand_heredoc(int n, char *s, t_minishell *mini, char	**res)
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
			i += expand_var(&s[i], res[n], &j, mini);
		}
		else if (s[i] == '"')
		{
			i++;
			handle_double(&s[i], &i, &j, mini, &n);
		}
		else if (s[i] == '\'' && mini->deuble == 0)
			handle_single(&(s[i]), &i, &j, mini, &n);
		else
			res[n][j++] = s[i++];
	}
	res[n][j] = '\0';
}

void	ft_check_dollar_heredoc(t_minishell *mini, char	*var, char	**res)
{
	char	**str;
	int		len;
	int		i;

	i = 0;
	str = ft_split(var, 32);
	while (str[i])
	{
		len = get_len(str[i], mini, 0);
		res[i] = ft_calloc(len + 1, 1);
		ft_expand_heredoc(i, str[i], mini, res);
		i++;
	}
	res[i] = NULL;
}
