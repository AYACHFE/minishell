/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:37:51 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/16 17:05:41 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	(void)ac;
	(void)av;
	(void)env;
	char *args[10];
	char *argecho[10];
	args[0] = ft_strdup("ls");
	args[1] = NULL;
	while (1)
	{ 
		str = readline("AYAC-->");
		if ((fork() == 0))
		{
			printf("test");
			if (str[0] == 'e')
			{
				execve("/bin/echo", argecho, env);
			}
			if ((str[0] == 'l' && str[1] == 's'))
				execve("/bin/ls", args, env);
			// puts("");
		}
		wait (NULL);
	}
}
