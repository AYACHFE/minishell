/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:37:51 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/19 13:19:51 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	(void) sig;
	if (sig == SIGINT)
	{
		rl_catch_signals = 1;
		close(0);
	}
	else if (sig == SIGQUIT)
		return ;
}

int	main(int ac, char **av, char **env)
{
	t_minishell	mini;
	int			fd;

	(void)ac;
	(void)av;
	ft_env_1(env, &mini);
	ft_add_declare(&mini);
	mini.exit_code = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	fd = dup(0);
	while (1)
	{
		rl_catch_signals = 0;
		dup2(fd, 0);
		built_in_cmd(&mini, env);
	}
}
