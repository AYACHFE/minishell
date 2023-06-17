/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:54:44 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/17 15:31:04 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parcing(t_minishell	*mini, t_cmd	*cmd, char *s)
{
	(void)mini;
	(void)s;
	to_struct(mini, cmd);
}

//this_is_the_function_that_places_every_cmd_in_a_atruct
void	to_struct_2(t_cmd	*cmd, t_cmd_info	*general_info, \
t_minishell	*mini)
{
	int		i;
	int		j;
	int		*tab;
	t_prep	prep;

	j = 0;
	i = 0;
	prep.eof_counter = 0;
	prep.fl = 0;
	prep.j = 0;
	prep.tab = 0;
	tab = args_counter(general_info);
	while (i < general_info->cmd_nb)
	{
		prep.tab = tab[i];
		tokenisation_1(&cmd[i], general_info, mini, &prep);
		prep.j++;
		i++;
	}
	free(tab);
}

//this_function_is_an_extention_of_to_struct_2
void	tokenisation_1(t_cmd	*cmd, t_cmd_info	*general_info, \
t_minishell	*mini, t_prep	*prep)
{
	int	l;

	l = 0;
	prep->eof_counter = 0;
	prep->fl = 0;
	init_tokenisation(cmd, general_info, prep->tab);
	while (general_info->str[prep->j] && (general_info->str[prep->j][0] != '|'))
	{
		if ((general_info->str[prep->j][0] == '>' || \
		general_info->str[prep->j][0] == '<') && mini->no_exp == 0)
			tokens_redirection(cmd, general_info, prep);
		else if (general_info->str[prep->j])
			cmd->args[l++] = ft_strdup(general_info->str[prep->j]);
		cmd->args[l] = NULL;
		prep->j++;
	}
	
	cmd->general_info = general_info;
	cmd->files[prep->fl] = NULL;
	cmd->eof[prep->eof_counter] = NULL;
}

//this_funct_puts_all_the_mutual_data
void	to_struct(t_minishell	*mini, t_cmd	*cmd)
{
	t_cmd_info	*general_info;
	int			i;

	i = 0;
	general_info = malloc(sizeof(t_cmd_info));
	init_general_info(general_info, mini);
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
	general_info->files_nb = general_info->append_nb + general_info->out_red_nb \
	+ general_info->in_red_nb;
	to_struct_2(cmd, general_info, mini);
}

//this_funct_searsh_for_redirections
void	tokens_redirection(t_cmd	*cmd, t_cmd_info	*general_info, \
t_prep	*prep)
{
	if (general_info->str[prep->j + 1] != NULL && (general_info->\
	str[prep->j][0] == '>' && general_info->str[prep->j][1] == '>'))
	{
		cmd->append = 1;
		cmd->files[prep->fl++] = ft_strjoin(">>", general_info->str[++prep->j]);
	}
	else if (general_info->str[prep->j + 1] != NULL && (\
	general_info->str[prep->j][0] == '>'))
	{
		cmd->out_red = 1;
		cmd->files[prep->fl++] = ft_strjoin("> ", general_info->str[++prep->j]);
	}
	else if (general_info->str[prep->j + 1] != NULL && (general_info->\
	str[prep->j][0] == '<' && general_info->str[prep->j][1] == '<'))
	{
		cmd->here_doc = 1;
		cmd->eof[prep->eof_counter++] = ft_strdup(general_info->str[++prep->j]);
	}
	else if (general_info->str[prep->j + 1] != NULL && (\
	general_info->str[prep->j][0] == '<'))
	{
		cmd->in_red = 1;
		cmd->files[prep->fl++] = ft_strjoin("< ", general_info->str[++prep->j]);
	}
}
