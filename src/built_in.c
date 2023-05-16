/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:45:13 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/16 19:46:24 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char *str)
{
	char *s;
	char *home;
	
	s = ft_substr(str, 3, ft_strlen(str) - 2);
	s = ft_strtrim(s, " ");
	home = getenv("HOME");
	if (ft_strlen(s) == 0)
	{
		chdir(home);
	}
	else if (chdir(s) != 0) 
	{
		perror("cd");
		return (1);
	}
	return (0);
}

void	ft_pwd()
{
	char	str[1024];

	getcwd(str, sizeof(str));
	printf("%s\n", str);
}
