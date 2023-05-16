/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:12:02 by rarraji           #+#    #+#             */
/*   Updated: 2023/05/16 21:18:33 by rarraji          ###   ########.fr       */
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