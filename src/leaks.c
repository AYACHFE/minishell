/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:13:16 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/16 15:11:30 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	to_free(t_cmd	*cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cmd->general_info->cmd_nb)
	{
		j = 0;
		while (cmd[i].args[j])
			free(cmd[i].args[j++]);
		j = 0;
		while (cmd[i].files[j])
			free(cmd[i].files[j++]);
		j = 0;
		while (cmd[i].eof[j])
			free(cmd[i].eof[j++]);
		free(cmd[i].args);
		free(cmd[i].files);
		free(cmd[i].eof);
		i++;
	}
	free(cmd->general_info);
	free(cmd);
}

void	to_free_1(t_minishell	*mini, char	**ret, char	*var, char	*str, char	*s)
{
	int	i;

	i = 0;
	while (mini->tmp_cmd[i])
		free(mini->tmp_cmd[i++]);
	free(mini->tmp_cmd);
	i = 0;
	while (ret[i])
		free(ret[i++]);
	free(ret);
	free(var);
	free(str);
	free(s);
}
