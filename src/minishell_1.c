/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:37:51 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/16 21:21:56 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int ac, char **av, char **env)
{
	int		i;
	int		j;
	// char	*str;
	// int 	status;
	t_minishell	mini;

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
		// str = readline("MINISHELL-3.2$ ");
		// mini.str = ft_split(str, ' ');
		// if ((fork() == 0))
		// {
			built_in_cmd(&mini, env);
			
			// if (ft_strncmp(mini.str[0], "echo", ft_strlen(mini.str[0])) == 0)
			// {
			// 	ft_echo(str);
			// }
			// else if (ft_strncmp(mini.str[0], "cd", ft_strlen(mini.str[0])) == 0)
			// {
			// 	ft_cd(&mini);
			// }
			// else if (ft_strncmp(mini.str[0], "pwd", ft_strlen(mini.str[0])) == 0)
			// {
			// 	ft_pwd();
			// }
			// else if (ft_strncmp(mini.str[0], "exit", ft_strlen(mini.str[0])) == 0)
			// {
			// 	puts("---");
			// 	exit(42);
			// }
			// else if (ft_strncmp(mini.str[0], "env", ft_strlen(mini.str[0])) == 0)
			// {
			// 	ft_env(env);
			// }
			// else if ((str[0] == 'l' && str[1] == 's'))
			// {
			// 	execve("/bin/ls", args, env);
			// }
			// else
			// {
			// 	perror(str);
			// }
		// }
		// wait(&status);
		// if (WIFEXITED(status) != 0)
		// {
		// 	// printf("---<<%d\n", WEXITSTATUS(status));
		// 	if (WEXITSTATUS(status) == 42)
		// 		exit (0);	
		// }
	}
}
