/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:12:02 by rarraji           #+#    #+#             */
/*   Updated: 2023/05/16 15:50:58 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(char *str)
{
    int i;
    int j;
    char s[8] = "echo -n ";

    i = 0;
    while(str[i] == s[i])
        i++;
    j = i;    
    if(i == 4)
    {
        write(1, "\n", 1);    
        return;
    }
    if (i < 5 || str[4] != ' ')
    {
        printf("command not found : %s\n", str);
        return;
    }
    while(str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    if (j != 8)
        write(1, "\n", 1);
        
}
