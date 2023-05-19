/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:12:02 by rarraji           #+#    #+#             */
/*   Updated: 2023/05/19 15:27:36 by rarraji          ###   ########.fr       */
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

void ft_export(t_minishell *mini) 
{
	ft_rem_var(mini->str ,mini);
}

void ft_rem_var(char **str, t_minishell *mini) 
{
	int i;
	int j;
	int d;
	int n;
	char **my_tmp;

	j = 0;
	n = 0;
	while (mini->my_env[j])
		j++;	
	my_tmp = malloc(sizeof(char *) * (j + mini->count_str)); 
	d = 0;
	j = 0;
	while (mini->my_env[d]) 
	{
		my_tmp[n] = ft_strdup(mini->my_env[d]);
		n++;
		d++;
	}
	i = 1;
	while(str[i])
	{
		my_tmp[n] = ft_strdup(mini->str[i]);
		n++;
		i++;
	}	
	my_tmp[n] = NULL; 
	i = 0;
	while (mini->my_env[i]) 
	{
		free(mini->my_env[i]);
		i++;
	}
	mini->my_env = my_tmp;
}


	
		































































//     i = 0;
//     while(str[i] == s[i])
//         i++;
//     j = i; 

//     if(i < 4)
//     { 
//         printf("test1");
//         write(1, "\n", 1);    
//         return;
//     }
//     else if (str[i] == '~')
//     {
//         printf("test2");
//         chdir(home);
//     }   
//     // if (i < 5 || str[4] != ' ')
//     // {
//     //     printf("command not found : %s\n", str);
//     //     return;
//     // }
//     else
//     {
//         while (str[i])
//         {
//             write(1, &str[i], 1);
//             i++;
//         }
		
//     }
//     if (j != 8)
//         write(1, "\n", 1);
		
// }