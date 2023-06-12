/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:12:02 by rarraji           #+#    #+#             */
/*   Updated: 2023/06/12 11:51:47 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(t_cmd	*cmd)
{
	
	int i;
	int	l;
	char *home;

	i = 2;
	l = 0;
	home = getenv("HOME");
	if (cmd->args[1] == NULL)
	{
		printf("\n");
		return;
	}
	if (cmd->args[1][0] == '~' && ft_strlen(cmd->args[1]) == 1)
		printf("%s\n", home);
	// else if (mini->str[1][0] == '$')
	// {
	// 	mini->variable = mini->str[1];
	// }
	else if (ft_strncmp(cmd->args[1], "-nn", ft_strlen(cmd->args[1])) == 0)
	{
		i = 2;
		while (ft_strncmp(cmd->args[i], "-nn", ft_strlen(cmd->args[i])) == 0)
			i++;
		while(cmd->args[i])
		{
			printf("%s", cmd->args[i]);
			if(cmd->args[i + 1] != '\0')
				printf(" ");
			i++;
		}
	}
	else
	{
		i = 1;
	   	while(cmd->args[i])
		{
			printf("%s", cmd->args[i]);
			if(cmd->args[i + 1] != '\0')
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
	while(str[i] != '=' && str[i] != '\0' && str[i] != '\"' && str[i] && str[i] != '-' && str[i] != '@' && str[i] != '$')
		i++;
	return(i);	
}

void	ft_tmp_my_env(t_minishell *mini)
{
	int	i;
	int	j;
	int	d;
	// int	tmp = 0;

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
			if (mini->my_env[i][j] == '=' && mini->my_env[i][j] != '\0')
			{
				mini->tmp_my_env[i][d] = mini->my_env[i][j];
				mini->tmp_my_env[i][++d] = '\"';
				d++;
				j++;
				while(mini->my_env[i][j] != '\0')
				{
					if(mini->my_env[i][j] == '$' || mini->my_env[i][j] == '\"')
					{
						mini->tmp_my_env[i][d] = '\\';
						mini->tmp_my_env[i][++d] = mini->my_env[i][j];
					}
					else
						mini->tmp_my_env[i][d] = mini->my_env[i][j];
					d++;
					j++;
					if(mini->my_env[i][j] == '\0')
						mini->tmp_my_env[i][d] = '\"';
				}
				if(mini->my_env[i][j] == '\0')
				{
					mini->tmp_my_env[i][d] = '\"';
					break;	
				}
			}
			else
				mini->tmp_my_env[i][d] = mini->my_env[i][j];
			d++;
			j++;
		}
		// if (mini->my_env[i][j] != '=' && mini->my_env[i][j + 1] != '\0')
		// 	mini->tmp_my_env[i][d] = '\"';
		mini->tmp_my_env[i][++d] = '\0';
		i++;
	}
	mini->tmp_my_env[i] = NULL;
	// i = 0;
	// while(mini->tmp_my_env[i])
	// {
	// 	printf("--->%s\n", mini->tmp_my_env[i]);
	// 	i++;
	// }
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
