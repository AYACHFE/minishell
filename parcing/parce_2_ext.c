/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_2_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:38:30 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/18 18:16:08 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//counts the nunber of arguments in every cmd so that i can allocate for it
int	*args_counter(t_cmd_info	*general_info)
{
	int	*tab;
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	tab = malloc(sizeof(int) * (general_info->cmd_nb + 1));
	while (general_info->str[i])
	{
		j = 0;
		while (general_info->str[i] && general_info->str[i][0] != '|')
		{
			if (args_counter_ext(general_info, &i, &j) == 1)
				break ;
			j++;
			i++;
		}
		tab[k] = j;
		i++;
		k++;
	}
	return (tab);
}

int	args_counter_ext(t_cmd_info	*general_info, int *i, int *j)
{
	if ((general_info->str[*i] && (general_info->str[*i][0] == '<' \
	|| general_info->str[*i][0] == '>')))
	{
		(*i)++;
		(*j)--;
	}
	if (!(general_info->str[*i + 1]))
	{
		(*j)++;
		return (1);
	}
	return (0);
}

//counts_the_nb_of_arguments
int	cmd_counter(t_minishell	*mini)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (mini->cmd[i])
	{
		if (mini->cmd[i][0] == '|')
			counter++;
		i++;
	}
	return (counter + 1);
}

void	init_general_info(t_cmd_info	*general_info, t_minishell	*mini)
{
	general_info->cmd_nb = cmd_counter(mini);
	general_info->pipe_nb = 0;
	general_info->append_nb = 0;
	general_info->here_doc_nb = 0;
	general_info->in_red_nb = 0;
	general_info->out_red_nb = 0;
	general_info->str = mini->tmp_cmd;
	general_info->exit_code = 0;
	general_info->in_file_exist = 0;
}

//initialise_data_needed_by_tokenisation_1
void	init_tokenisation(t_cmd	*cmd, t_cmd_info	*general_info, int tab)
{
	cmd->append = 0;
	cmd->out_red = 0;
	cmd->out_red = 0;
	cmd->here_doc = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->args = malloc(sizeof(char *) * (tab + 2));
	cmd->files = malloc(sizeof(char *) * (general_info->files_nb + 1));
	cmd->eof = malloc(sizeof(char *) * (general_info->here_doc_nb + 1));
}
