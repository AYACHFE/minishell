/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:50:54 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/16 22:53:57 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_cmd	*cmd, t_minishell	*mini)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (mini->my_env[i] != NULL)
	{
		ft_cd_ext(mini, i, &check);
		i++;
	}
	if (check == 0 && !(cmd->args[1]))
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (cmd->args[1] == NULL)
		chdir(getenv("HOME"));
	else if (chdir(cmd->args[1]) != 0)
	{
		mini->exit_code = 1;
		perror("minishell: ");
		return (1);
	}
	return (0);
}

void	ft_cd_ext(t_minishell	*mini, int i, int *check)
{
	if (ft_strncmp(mini->my_env[i], "HOME", ft_cnt(mini->my_env[i])) == 0)
	{
		*check = 1;
		return ;
	}
}

void	ft_pwd(void)
{
	char	str[1024];

	getcwd(str, sizeof(str));
	printf("%s\n", str);
}
