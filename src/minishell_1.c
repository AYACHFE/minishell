/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:37:51 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/16 14:55:36 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main(int ac, char **av, char **env)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	i = 0;
// 	j = 0;
// 	(void)ac;
// 	(void)av;
// 	(void)env;
// 	char *args[10];
// 	char *argecho[10];
// 	args[0] = ft_strdup("ls");
// 	args[1] = NULL;
// 	argecho[0] = ft_strdup("echo");
// 	argecho[1] = NULL;
// 	while (1)
// 	{ 
// 		str = readline("AYAC-->");
// 		if ((fork() == 0))
// 		{
// 			printf("test");
// 			if (str[0] == 'e')
// 			{
// 				execve("/bin/echo", argecho, env);
// 			}
// 			if ((str[0] == 'l' && str[1] == 's'))
// 				execve("/bin/ls", args, env);
// 			// puts("");
// 		}
// 		wait (NULL);
// 	}
// }

int main(int argc, char **argv, char **env)
{
    char *args[2];
    char *argecho[2];
    args[0] = "/bin/ls";
    args[1] = NULL;
    argecho[0] = "/bin/echo";
    argecho[1] = NULL;
    
	(void)argc;
	(void)argv;
	(void)env;
    while (1)
    { 
        char *str = readline("AYAC-->");
        
        if (str == NULL)
        {
            // Exit the program if readline returns NULL (e.g., Ctrl+D is pressed)
            break;
        }
        
        if (fork() == 0)
        {
            if (str[0] == 'e')
            {
                execve(argecho[0], argecho, env);
                perror("execve");
                exit(EXIT_FAILURE);
            }
            else if (str[0] == 'l' && str[1] == 's')
            {
                execve(args[0], args, env);
                perror("execve");
                exit(EXIT_FAILURE);
            }
            
            // Child process should exit if no valid command is entered
            exit(EXIT_FAILURE);
        }
        
        wait(NULL);
        free(str);
    }
    
    return 0;
}

// #include <stdio.h>
// #include <unistd.h>

// int main() {
//     char *args[] = {"ls", "-l", NULL};
//     char *env[] = {NULL};

//     if (execve("/bin/ls", args, env) == -1) {
//         perror("execve");
//         return 1;
//     }

//     return 0;
// }