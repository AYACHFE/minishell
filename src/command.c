/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:12:02 by rarraji           #+#    #+#             */
/*   Updated: 2023/05/19 13:43:36 by aachfenn         ###   ########.fr       */
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

void	ft_env(char **env, t_minishell *mini)
{
	int i;

	i = 0;
	(void)env;
	while(mini->my_env[i])
	{
		printf("%s\n", mini->my_env[i]);
		i++;	
	}
}

char **ft_env_1(char **env, t_minishell *mini)
{
	int i;

	i = 0;
	while(env[i])
		i++;
	mini->my_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while(env[i])
	{
		mini->my_env[i] = ft_strdup(env[i]);
		i++;	
	}
	mini->my_env[i] = 0;
	return (mini->my_env);
}







int ft_cnt (char *str)
{
	int i;
	i = 0;
	while(str[i] != '=' && str[i] != '\0')
		i++;
	return(i);	
}

// void ft_unste(t_minishell *mini) 
// {
// 	int i;
// 	int j;
// 	int l;

// 	i = 1;
// 	l = 0;
// 	while (i < mini->count_str) {
// 		j = 0;
// 		while (mini->my_env[j]) {
// 			if (ft_strncmp(mini->str[i], mini->my_env[j], ft_cnt(mini->my_env[j])) != 0)
// 				j++;
// 			else {
// 				j++;
// 				l++;
// 				break;
// 			}
// 		}
// 		i++;
// 	}
// 	ft_rem_var(mini->str ,mini, l);
// }

// void ft_rem_var(char **str, t_minishell *mini, int l) 
// {
// 	int i;
// 	int j;
// 	int d;
// 	int n;
// 	int g;
// 	char **my_tmp;

// 	j = 0;
// 	n = 0;
// 	while (mini->my_env[j])
// 		j++;
// 	my_tmp = malloc(sizeof(char *) * (j - l + 1)); 
// 	d = 0;
// 	j = 0;
// 	while (mini->my_env[d]) 
// 	{
// 		i = 1;
// 		while (i < mini->count_str) 
// 		{
// 			g = ft_strncmp(mini->my_env[d] ,str[i],ft_cnt(mini->my_env[d]));
// 			if (g != 0)
// 			{
// 				my_tmp[n] = ft_strdup(mini->my_env[d]);
// 				n++;
// 				i++;
// 			}
// 			else
// 				i++;
// 		}
// 		d++;
// 	}
// 	my_tmp[n] = NULL; 
// 	i = 0;
// 	while (my_tmp[i]) 
// 	{
// 		printf("%s\n", my_tmp[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (mini->my_env[i]) 
// 	{
// 		free(mini->my_env[i]);
// 		i++;
// 	}
// 	mini->my_env = my_tmp;
// }
