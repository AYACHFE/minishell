/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 07:31:26 by rarraji           #+#    #+#             */
/*   Updated: 2023/05/29 17:58:01 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// int ft_hsb(char *s, int l)
// {
//     char c;
//     int  i;

//     i = 0;
//     if (l == 0)
//         c = '\'';
//     else
//         c = '\"';
//     while (s[i] != c && s[i])
//         i++;
//     return (i);           
// }

// int ft_hsb1(char *s)
// {
//     int  i;

//     i = 0;
//     while (ft_isalpha(s[i]) == 1 || ft_isdigit(s[i]) == 1 || s[i] == '_')
//         i++;
//     return (i);
// }
 


// char    *ft_change_var(char *str, t_minishell *mini)
// {
//     int i;
//     int j;
//     int single;
//     // int deuble;
//     mini = NULL;

//     single = 0;
//     char *s;
//     // char *val;
//     i = 0;
//     j = 0;

//     while (str[i])
//     {
//         if (str[i] == '\'')
//         {
//             j = i + 1;
//             while (str[j] != '\'')
//                 j++;
//             s = ft_substr(str, i + 1, ft_hsb(str, 0));
//             printf("--->%d\n", ft_hsb(str, 0));
//             i = j + 1;
//             single = 0;
//         }
//         if (str[i] == '$')
//         {
//             j = i + 1;
//             while (str[j] != '\0')
//                 j++;
//             s = ft_substr(str, i + 1, ft_hsb(str, 0));
//             // printf("--->%s\n", s);
//             i = j;
//             single = 0;
//         }
//         else
//         {
//             j = i;
//             while (ft_isalpha(str[j]) == 1 || ft_isdigit(str[j]) == 1 || str[j] == '_')
//                 j++;
//             // printf("%d\n", j);
//             s = ft_substr(str, i, ft_hsb1(str));
//             // printf("--->%s\n", s);
//             i = j;        
//         }    
//     }
//     return (s);
        // if (str[i] == '\"')
        // {
        //     deuble = 1;
        //     i++;
        //     if (str[i] == '\'')
        //         single = i;
        //     if (str[i] == '$')
        //     {
        //         i++;
        //         if (single != 0)
        //         {
        //             j = i;
        //             while (ft_isalpha(str[j]) == 1 || ft_isdigit(str[j]) == 1 || str[j] == '_')
        //                 j++;
        //             s = ft_substr(str, i, ft_hsb1(str)); 
        //             // val = ft_chek_val(s);
        //             printf("--->%s\n", s);
        //             i = j;
        //             single = 0;
        //             free (s);
        //         }
        //         else
        //         {
        //             j = i;
        //             printf("1-->%d\n", j);
        //             while (ft_isalpha(str[j]) == 1 || ft_isdigit(str[j]) == 1 || str[j] == '_')
        //                 j++;
        //             s = ft_substr(str, i, ft_hsb1(str)); 
        //             // val = ft_chek_val(s);
        //             printf("2-->%d\n", ft_hsb1(str));
        //             printf("--->%s\n", s);
        //             i = j;
        //             free (s);
        //         }
        //     }
              
        // }
        // if (str[i] == '$')
        // {
        //     j = i + 1;
        //     while (str[j] != '\0')
        //         j++;
        //     s = ft_substr(str, i + 1, ft_hsb(str, 0));
        //     printf("--->%s\n", s);
        //     i = j;
        //     single = 0;
        // }
        // i++;
    // }

    
}




















void    ft_check_dollar(t_minishell *mini)
{
    int i;
    int j;
    int d;
    int tmp;

    i = 0;
    j = 0;
    d = 0;
    tmp = 0;
    mini->tmp_cmd = malloc(sizeof(char *) * (mini->cmd_nb + 1));
    while (mini->cmd[i])
    {
        d = 0;
        // if (mini->cmd[i][d] == '\"')
        //     d++;
        while(mini->cmd[i][d])
        {
            if (mini->cmd[i][d] == '$')
                tmp++;
            d++;    
        }
        if (tmp > 0)
        {
            mini->tmp_cmd[j] = ft_change_var(mini->cmd[i], mini);
            // printf("11------>%s\n", mini->tmp_cmd[j]);
            j++;
        }
        else
        {
            mini->tmp_cmd[j] = ft_substr(mini->cmd[i], 0, ft_strlen(mini->cmd[i]));
            // printf("22------>%s\n", mini->tmp_cmd[j]);
            j++;
        }
        tmp = 0;
        i++;
    }
    mini->tmp_cmd[j] = NULL; 
    i = 0;
    while (mini->tmp_cmd[i])
	{
		printf("*%s*\n", mini->tmp_cmd[i]);
		i++;
	}     
}