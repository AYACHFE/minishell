/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:12:02 by rarraji           #+#    #+#             */
/*   Updated: 2023/06/18 14:27:49 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_putstr_fd1(char *s, int fd)
{
    int    i;
    int sp;

    i = 0;
    sp = 0;
    if (!s)
        return ;
    while(s[i] == ' ' && s[i])
        i++;
    while (s[i] != '\0')
    {
            while((s[i] == ' ' || s[i] == '\t' ) && s[i])
            {
                i++;
                sp = 1;
            }
            if(sp == 1)
            {
                sp = 0;
                write(fd, " ", 1);
            }
            write(fd, &s[i], 1);
            i++;
    }
}
 
void ft_echo(t_cmd    *cmd)
{

    int i;
    int    l;

    // printf("''%s''\n", cmd->args[1]);
    i = 2;
    l = 0;
    if (cmd->args[1]&& ft_strlen(cmd->args[1]) == 0)
    {
        printf("\n");
        return;
    }
    if (cmd->args[1] == NULL)
    {
        printf("\n");
        return;
    }
    else if (ft_strncmp(cmd->args[1], "-nn", ft_strlen(cmd->args[1])) == 0)
    {
        i = 2;
        while (ft_strncmp(cmd->args[i], "-nn", ft_strlen(cmd->args[i])) == 0)
            i++;
        while(cmd->args[i])
        {

            ft_putstr_fd(cmd->args[i], 1);
            if(cmd->args[i + 1] != '\0')
                write(1, " ", 1);
            i++;
        }
    }
    else
    {
        i = 1;
           while(cmd->args[i])
        {

            ft_putstr_fd1(cmd->args[i], 1);
            if(cmd->args[i + 1] != '\0')
                write(1, " ", 1);
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


////////////////norm
void	ft_tmp_my_env_3(t_minishell	*mini, int *i, int *d, int *j)
{
	if(mini->my_env[*i][*j] == '$' || mini->my_env[*i][*j] == '\"')
	{
		mini->tmp_my_env[*i][*d] = '\\';
		mini->tmp_my_env[*i][++(*d)] = mini->my_env[*i][*j];
	}
	else
		mini->tmp_my_env[*i][*d] = mini->my_env[*i][*j];
	(*d)++;
	(*j)++;
	if(mini->my_env[*i][*j] == '\0')
		mini->tmp_my_env[*i][*d] = '\"';
}

void	ft_tmp_my_env_2(t_minishell	*mini, int *i, int *d, int *j)
{
	while(mini->my_env[*i][*j])
	{
		if (mini->my_env[*i][*j] == '=' && mini->my_env[*i][*j] != '\0')
		{
			mini->tmp_my_env[*i][*d] = mini->my_env[*i][*j];
			mini->tmp_my_env[*i][++(*d)] = '\"';
			(*d)++;
			(*j)++;
			while(mini->my_env[*i][*j] != '\0')
				ft_tmp_my_env_3(mini, i, d, j);
			if(mini->my_env[*i][*j] == '\0')
			{
				mini->tmp_my_env[*i][*d] = '\"';
				return ;	
			}
		}
		else
			mini->tmp_my_env[*i][*d] = mini->my_env[*i][*j];
		(*d)++;
		(*j)++;
	}
}

void	ft_tmp_my_env_1(t_minishell	*mini)
{
	int	i;
	int	j;
	int	d;

	i = 0;
	while(mini->my_env[i])
	{
		j = 0;
		while(mini->my_env[i][j])
			j++;
		mini->tmp_my_env[i] = malloc(j + 4);
		j = 0;
		d = 0;
		ft_tmp_my_env_2(mini, &i, &d, &j);
		mini->tmp_my_env[i][++d] = '\0';
		i++;
	}
	mini->tmp_my_env[i] = NULL;
}

void	ft_tmp_my_env(t_minishell *mini)
{
	int	i;

	i = 0;
	while (mini->my_env[i])
		i++;
	mini->tmp_my_env = malloc(sizeof(char *) * (i + 1));
	ft_tmp_my_env_1(mini);
}
////////////////norm

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
