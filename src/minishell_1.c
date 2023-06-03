/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:37:51 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/03 19:31:34 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		built_in_cmd(&mini, env);
	}
}
