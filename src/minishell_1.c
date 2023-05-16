/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:37:51 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/16 18:17:48 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int ac, char **av, char **env)
{
	int		i;
	int		j;
	char	*str;
	int status;

	i = 0;
	j = 0;
	(void)ac;
	(void)av;
	(void)env;
	char *args[10];
	args[0] = ft_strdup("ls");
	args[1] = NULL;
	while (1)
	{ 
		str = readline("MINISHELL-3.2$ ");
		if ((fork() == 0))
		{
			if (str[0] == 'e' && str[1] == 'c')
			{
				ft_echo(str);
			}
			else if (str[0] == 'c' && str[1] == 'd')
			{
				ft_cd(str);
			}
			else if (str[0] == 'p' && str[1] == 'w' && str[2] == 'd')
			{
				ft_pwd();
			}
			else if (str[0] == 'e' && str[1] == 'x')
			{
				exit(42);
			}
			else if ((str[0] == 'l' && str[1] == 's'))
			{
				execve("/bin/ls", args, env);
			}
		}
		wait(&status);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 42)
				exit(0);
		}
	}
}
