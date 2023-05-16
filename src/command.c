/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:12:02 by rarraji           #+#    #+#             */
/*   Updated: 2023/05/16 21:25:53 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(t_minishell *mini)
{
	int i;

	i = 2;
	mini->home = getenv("HOME");

	if (mini->str[1][0] == '~' && ft_strlen(mini->str[1]) == 1)
		printf("%s\n", mini->home);
	else if (ft_strncmp(mini->str[1], "-n", ft_strlen("-n")) == 0)
	{
		while(mini->str[i])
		{
			printf("%s", mini->str[i]);
			if(mini->str[i + 1] != '\0')
				printf(" ");
			i++;
		}
	}
	else if (mini->str[1][0] == '$')
		mini->variable = mini->str[1];
	else
	{
		i = 1;
	   	while(mini->str[i])
		{
			printf("%s", mini->str[i]);
			if(mini->str[i + 1] != '\0')
				printf(" ");
			i++;
		}
		printf("\n");
	}
}
