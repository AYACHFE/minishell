/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:18:58 by rarraji           #+#    #+#             */
/*   Updated: 2023/05/24 21:50:38 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_change_var(char *str, t_minishell *mini)
{
    int i;
    int j;
    char *s;
     
    i = 0;

    while(str[i])
        i++;
    s = malloc(i);
    i=1;
    j = 0;
    while(str[i])
    {
        s[j] = str[i];
        j++;
        i++;
    }
    s[j] = '\0';
    j = 0;
    i = 0;
    while (mini->my_env[i])
    {
        if (ft_strncmp(mini->my_env[i], s, ft_cnt(s)) == 0)
        {
            while (mini->my_env[i][j])
            {
                if (mini->my_env[i][j] == '=')
                    break; 
                j++;            
            }
        }
        if (mini->my_env[i][j] == '=')
            break;
        else
            i++;    
    }
    free(s);
    if (mini->my_env[i] != '\0')
    {
        free(str);
        str = ft_substr(mini->my_env[i], j+1, ft_strlen(mini->my_env[i]));
    }
    return (str);    
}

void    ft_check_dollar(t_minishell *mini)
{
    int i;
    int j;

    i = 0;
    j = 0;
    // printf("--->%d\n", mini->cmd_nb);
    mini->tmp_cmd = malloc(sizeof(char *) * (mini->cmd_nb + 1));
    while (mini->cmd[i])
    {
            if(mini->cmd[i][0] == '$')
            {
                mini->tmp_cmd[j] = ft_change_var(mini->cmd[i], mini);  
                j++;
            }
            else
            {
                mini->tmp_cmd[j] = ft_substr(mini->cmd[i], 0, ft_strlen(mini->cmd[i]));
                j++;
            }
            i++;
    }
    mini->tmp_cmd[j] = NULL; 
    i = 0;
    // while (mini->tmp_cmd[i])
	// {
	// 	printf("*%s*\n", mini->tmp_cmd[i]);
	// 	i++;
	// }     
}