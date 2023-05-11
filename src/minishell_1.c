/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:37:51 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/11 15:02:52 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd(char	*str)
{
	void(str);
}

int main()
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (1)
	{
		str = readline("AYAC-->");
		printf("%s\n", str);
		// if (check_cmd(str))
		execv();
	}
}
