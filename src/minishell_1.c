/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:37:51 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/18 11:11:52 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int ac, char **av, char **env)
{
	t_minishell	mini;

	(void)ac;
	(void)av;
	ft_env_1(env, &mini);
	while (1)
	{
		built_in_cmd(&mini, env);
	}
}
