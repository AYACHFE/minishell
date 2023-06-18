/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:37:51 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/18 14:28:25 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void sigint_handler(int sig) 
{
	(void) sig;
	write(1, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

int main(int ac, char **av, char **env)
{
	t_minishell	mini;

	(void)ac;
	(void)av;
	ft_env_1(env, &mini);
	ft_add_declare(&mini);
	mini.exit_code = 0;
	while (1)
	{
		signal(SIGINT, sigint_handler);
		built_in_cmd(&mini, env);
	}
}
