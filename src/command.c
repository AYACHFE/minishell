/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:12:02 by rarraji           #+#    #+#             */
/*   Updated: 2023/05/18 14:21:22 by aachfenn         ###   ########.fr       */
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
		// mini->my_env[i] = ft_strdup(env[i]);
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
	mini->my_env = malloc(sizeof(char *) *(i + 1));
	i = 0;
	while(env[i])
	{
		mini->my_env[i] = ft_strdup(env[i]);
		printf("i == %d\n", i);
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

void	ft_unste(t_minishell *mini)
{
	int		i;
	int		j;
	int		l;

	i = 0;
	l = 0;
	while(mini->str[i])
	{	
		j = 0;
		while(mini->my_env[j])
		{
			if (ft_strncmp(mini->str[i], mini->my_env[j], ft_cnt(mini->str[i])) != 0)
				j++;
			else
			{
				j++;
				l++;
				break;
			}
		}
		i++;
	}
	ft_rem_var(mini->str, mini, l);
}

void	ft_rem_var(char **str, t_minishell *mini, int l)
{
	int 	i;
	int		j;
	int		d;
	char 	**my_tmp;

	j = 0;
	while (mini->my_env[j])
		j++;
	my_tmp = malloc(sizeof(char *) * (j - l + 1));
	d = 0;
	j = 0;
	while(mini->my_env[d])
	{
		i = 1;
		while (mini->str[i])
		{
			if (ft_strncmp(str[i], mini->my_env[d], ft_cnt(str[i])) != 0)
			{
				my_tmp[j] = ft_strdup(mini->my_env[d]);
				printf("%s\n", my_tmp[j]);
				j++;
				break;
			}
			else
				i++;
		}
		d++;
	}
	my_tmp[j] = 0;
	i = 0;
	while (mini->my_env[i])
	{
		free(mini->my_env[i]);
		i++;
	}
	free(mini->my_env);
	ft_env_1(my_tmp, mini);
	// mini->my_env = malloc(sizeof(char *) * (j - l + 1));
}
