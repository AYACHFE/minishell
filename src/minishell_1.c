/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:37:51 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/16 18:52:38 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int ac, char **av, char **env)
{
	int		i;
	int		j;
	char	*str;
	int status;
	// t_minishell	*mini;

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
		// mini->str = ft_split(str, ' ');
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
			else if (ft_strncmp(str, "pwd", 3) == 0)
			{
				ft_pwd();
			}
			else if (ft_strncmp(str, "exit", 4) == 0)
			{
				exit(42);
			}
			else if ((str[0] == 'l' && str[1] == 's'))
			{
				execve("/bin/ls", args, env);
			}
			else
			{
				perror(str);
			}
		}
		wait(&status);
		if (WEXITSTATUS(status) == 42)
			exit(0);
	}
}
