/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:54:44 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/23 21:48:52 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_counter(t_minishell	*mini)
{
	int i;
	int	counter;

	i = 0;
	counter = 0;
	while (mini->cmd[i])
	{
		if (mini->cmd[i][0] == '|')
			counter++;
		else if (mini->cmd[i][0] == '>')
			counter++;
		else if (mini->cmd[i][0] == '<')
			counter++;
		i++;
	}
	return (counter + 1);
}

void	to_struct_2(t_cmd	*cmd, int	index)
{
	int		i;
	int		j;
	char	**builtin;

	builtin = ft_split("echo ls cat pwd wc", 32);
	i = 0;
	j = 0;
	while (cmd->general_info->str[i])
	{
		j = 0;
		while (builtin[j])
		{
			if (ft_strncmp(cmd->general_info->str[i], builtin[j], ft_strlen(builtin[j])))
			{
				
				return (j);
			}
			j++;	
		}
		i++;
	}
}

void	to_struct(t_minishell	*mini)
{
	int	i;
	t_cmd	*cmd;
	t_cmd_info	*general_info;

	i = 0;

	//init the struct 
	cmd = malloc(sizeof(t_cmd) * cmd_counter(mini));
	general_info = malloc(sizeof(t_cmd_info));
	general_info->cmd_nb = cmd_counter(mini);
	printf("cmd_counter == %d\n", general_info->cmd_nb);
	general_info->pipe_nb = 0;
	general_info->append_nb = 0;
	general_info->here_doc_nb = 0;
	general_info->in_red_nb = 0;
	general_info->out_red_nb = 0;
	general_info->str = mini->cmd;
	while (mini->cmd[i])
	{
		if (mini->cmd[i][0] == '|')
			general_info->pipe_nb++;
		else if (mini->cmd[i][0] == '>' && mini->cmd[i][1] == '>')
			general_info->append_nb++;
		else if (mini->cmd[i][0] == '<' && mini->cmd[i][1] == '<')
			general_info->here_doc_nb++;
		else if (mini->cmd[i][0] == '>')
			general_info->out_red_nb++;
		else if (mini->cmd[i][0] == '<')
			general_info->in_red_nb++;
		i++;
	}
	printf("general_info->pipe_nb == %d\n", general_info->pipe_nb);
	printf("general_info->append_nb == %d\n", general_info->append_nb);
	printf("general_info->here_doc_nb == %d\n", general_info->here_doc_nb);
	printf("general_info->in_red_nb == %d\n", general_info->in_red_nb);
	printf("general_info->out_red_nb == %d\n", general_info->out_red_nb);
	int	index;
	
	while (index < general_info->cmd_nb)
	{
		to_struct_2(cmd, index);
	}
}