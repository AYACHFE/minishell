/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:06:09 by rarraji           #+#    #+#             */
/*   Updated: 2023/05/22 10:50:32 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int ft_double_single_quote(char *str)
{
    int     i;
    int     j;
    int     tmp;
    char    c;

    i = 0;
    tmp = 1;
    while(str[i])
    {
        if(str[i] == '"' || str[i] == '\'')
        {
                tmp = 0;
                j = i + 1;
                c = str[i];
            while (str[j])
            {
                if(str[j] == c)
                {
                    tmp = 1;
                    break;
                }
                else
                    j++;
            }
            i = j + 1;
        }
        else
            i++;
    }
    return (tmp);
}