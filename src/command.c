/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:12:02 by rarraji           #+#    #+#             */
/*   Updated: 2023/06/19 11:07:50 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd1(char *s, int fd)
{
	int	i;
	int	sp;

	i = 0;
	sp = 0;
	if (!s)
		return ;
	while (s[i] == ' ' && s[i])
		i++;
	while (s[i] != '\0')
	{
		while ((s[i] == ' ' || s[i] == '\t' ) && s[i])
		{
			i++;
			sp = 1;
		}
		if (sp == 1)
		{
			sp = 0;
			write(fd, " ", 1);
		}
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_echo_1(t_cmd	*cmd)
{
	int	i;

	i = 2;
	while (ft_strncmp(cmd->args[i], "-nn", ft_strlen(cmd->args[i])) == 0)
		i++;
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1] != '\0')
			write(1, " ", 1);
		i++;
	}
}

void	ft_echo(t_cmd	*cmd)
{
	int	i;

	if ((cmd->args[1] && ft_strlen(cmd->args[1]) == 0) || cmd->args[1] == NULL)
	{
		printf("\n");
		return ;
	}
	else if (ft_strncmp(cmd->args[1], "-nn", ft_strlen(cmd->args[1])) == 0)
		ft_echo_1(cmd);
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			ft_putstr_fd1(cmd->args[i], 1);
			if (cmd->args[i + 1] != '\0' && cmd->args[i][0] != ' ')
				write(1, " ", 1);
			i++;
		}
		printf("\n");
	}
}

void	ft_env(char **env, t_minishell *mini)
{
	int	i;

	i = 0;
	(void)env;
	while (mini->my_env[i])
	{
		printf("%s\n", mini->my_env[i]);
		i++;
	}
}

char	**ft_env_1(char **env, t_minishell *mini)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	mini->my_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		mini->my_env[i] = ft_strdup(env[i]);
		i++;
	}
	mini->my_env[i] = 0;
	return (mini->my_env);
}
