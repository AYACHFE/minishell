/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:12:02 by rarraji           #+#    #+#             */
/*   Updated: 2023/05/24 21:41:59 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(t_minishell *mini)
{
	int i;
	int	l;

	i = 2;
	l = 0;
	mini->home = getenv("HOME");
	if (mini->str[1] == NULL)
		return;
	if (mini->str[1][0] == '~' && ft_strlen(mini->str[1]) == 1)
		printf("%s\n", mini->home);
	else if (mini->str[1][0] == '$')
	{
		mini->variable = mini->str[1];
	}
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

void	ft_tmp_my_env(t_minishell *mini)
{
	int	i;
	int	j;
	int	d;

	i = 0;
	j = 0;
	while (mini->my_env[i])
		i++;
	mini->tmp_my_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while(mini->my_env[i])
	{
		j = 0;
		while(mini->my_env[i][j])
			j++;
		mini->tmp_my_env[i] = malloc(j + 3);
		j = 0;
		d = 0;
		while(mini->my_env[i][j])
		{
			mini->tmp_my_env[i][d] = mini->my_env[i][j];
			if (mini->my_env[i][j] == '=' || mini->my_env[i][j + 1] == '\0')
				mini->tmp_my_env[i][++d] = '\"';
			d++;
			j++;
		}
		mini->tmp_my_env[i][d] = '\0';
		i++;
	}
	mini->tmp_my_env[i] = NULL;
}

void	ft_add_declare(t_minishell *mini)
{
	int i;
	int j = 0;
	char s[12] ="declare -x ";
	i = 0;
	ft_tmp_my_env(mini);
	while (mini->tmp_my_env[i])
		i++;
	mini->my_export = malloc(sizeof(char *) * (i + 1));
	while(j < i)
	{
		mini->my_export[j] = ft_strjoin(s, mini->tmp_my_env[j]);
		j++;
	}
	mini->my_export[j] = NULL;
}

void	ft_tmp_my_env_pos(t_minishell *mini, int	pos)
{
	int	i;
	int	j;
	int	d;

	i = 0;
	j = 0;
	mini->tmp_my_env = malloc(sizeof(char *) * (pos + 1));
	j = 0;
	while(mini->my_export[pos][j])
		j++;
	mini->tmp_my_env[pos] = malloc(j + 3);
	j = 0;
	d = 0;
	while(mini->my_export[pos][j])
	{
		mini->tmp_my_env[pos][d] = mini->my_export[pos][j];
		if (mini->my_export[pos][j] == '=' || mini->my_export[pos][j + 1] == '\0')
			mini->tmp_my_env[pos][++d] = '"';
		d++;
		j++;
	}
	mini->tmp_my_env[pos][d] = '\0';
	mini->tmp_my_env[pos + 1] = NULL;
}

// void	ft_add_declare_in_pos(t_minishell *mini)
// {
// 	int i;
// 	int j = 0;
// 	char s[12] ="declare -x ";
// 	int	pos;
	
// 	i = 0;
// 	pos = 0;
// 	while (mini->my_env[pos])
// 			pos++;
// 	ft_tmp_my_env_pos(mini, pos);
// 	while (mini->my_env[i])
// 		i++;
// 	printf("== %d\n", i);
// 	mini->my_export = malloc(sizeof(char *) * (i + 1));
// 	// while(j < i)
// 	// {
// 		mini->my_export[pos] = ft_strjoin(s, mini->tmp_my_env[pos]);
// 	// 	j++;
// 	// }
// 	mini->my_export[j + 1] = NULL;
// }

	
		































































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