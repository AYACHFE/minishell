/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:54:44 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/15 15:38:43 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//this_is_the_function_that_places_every_cmd_in_a_atruct
void	to_struct_2(t_cmd	*cmd, t_cmd_info	*general_info, t_minishell	*mini)
{
	int	i;
	int	j;
	int	l;
	int	*tab;
	int	fl;
	
	l = 0;
	j = 0;
	i = 0;
	fl = 0;
	tab = args_counter(general_info);
	while (i < general_info->cmd_nb)
	{
		tokenisation_1(&cmd[i], general_info, mini, &j, tab[i]);
		j++;
		i++;
	}
	free(tab);
	// print_all_data(cmd, general_info);
}

//this_function_is_an_extention_of_to_struct_2
void	tokenisation_1(t_cmd	*cmd, t_cmd_info	*general_info, t_minishell	*mini, int *j, int	tab)
{
	int	l;
	int	eof_counter;
	int	fl;
	
	l = 0;
	fl = 0;
	eof_counter = 0;
	l = 0;
	fl = 0;
	init_tokenisation(cmd, general_info, tab);
	while (general_info->str[*j] && (general_info->str[*j][0] != '|'))
	{
		if ((general_info->str[*j][0] == '>' || general_info->str[*j][0] == '<') && mini->no_exp == 0)
			tokens_redirection(cmd, general_info, j, &eof_counter, &fl);
		else if (general_info->str[*j])
			cmd->args[l++] = ft_strdup(general_info->str[*j]);
		cmd->args[l] = NULL;
		(*j)++;
	}
	cmd->general_info = general_info;
	cmd->files[fl] = NULL;
	cmd->eof[eof_counter] = NULL;
}

//initialise_data_needed_by_tokenisation_1
void	init_tokenisation(t_cmd	*cmd, t_cmd_info	*general_info, int	tab)
{
	cmd->append = 0;
	cmd->out_red = 0;
	cmd->out_red = 0;
	cmd->here_doc = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->args = malloc(sizeof(char *) * (tab + 1));
	cmd->files = malloc(sizeof(char *) * (general_info->files_nb + 1));
	cmd->eof = malloc(sizeof(char *) * (general_info->here_doc_nb + 1));
}

//this_funct_searsh_for_redirections
void	tokens_redirection(t_cmd	*cmd, t_cmd_info	*general_info, int *j, int *eof_counter, int *fl)
{
	if (general_info->str[*j + 1] != NULL && (general_info->str[*j][0] == '>' && general_info->str[*j][1] == '>'))
	{
		cmd->append = 1;
		cmd->files[(*fl)++] = ft_strjoin(">>", general_info->str[++(*j)]);
	}
	else if (general_info->str[*j + 1] != NULL && (general_info->str[*j][0] == '>'))
	{
		cmd->out_red = 1;
		cmd->files[(*fl)++] = ft_strjoin("> ", general_info->str[++(*j)]);
	}
	else if (general_info->str[*j + 1] != NULL && (general_info->str[*j][0] == '<' && general_info->str[*j][1] == '<'))
	{
		cmd->here_doc = 1;
		cmd->eof[(*eof_counter)++] = ft_strdup(general_info->str[++(*j)]);
	}
	else if (general_info->str[*j + 1] != NULL && (general_info->str[*j][0] == '<'))
	{
		cmd->in_red = 1;
		cmd->files[(*fl)++] = ft_strjoin("< ", general_info->str[++(*j)]);
	}
}
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
			if (general_info->str[i] && (general_info->str[i][0] == '<' || general_info->str[i][0] == '>'))
			{
				i++;
				j--;
			}
			if (!(general_info->str[i + 1]))
			{
				j++;
				break ;
			}
			j++;
			i++;
		}
		tab[k] = j;
		i++;
		k++;
	}
	return (tab);
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
	// general_info = malloc(sizeof(t_cmd_info));
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

//this function should be removed after its just helps to debug
void	print_all_data(t_cmd	*cmd, t_cmd_info	*general_info)
{
	//prints all the struct data , and the data is about the cmds
	int	i;
	int	j;
	int	eof_counter;
	// int	fl;
	int	l;

	i = 0;
	j = 0;	
	while (i < general_info->cmd_nb)
	{
		l = 0;
		while (cmd[i].args[l] != NULL)
		{
			printf("--->cmd[%d].args[%d]--> %s\n",i, l, cmd[i].args[l]);
			l++;
		}
		// fl = 0;
		// while (cmd[i].files[fl])
		// {
		// 	printf("cmd[%d].files[%d] == %s\n", i, fl, cmd[i].files[fl]);
		// 	fl++;
		// }
		// 	if (cmd[i].append == 1 || cmd[i].here_doc == 1 || cmd[i].out_red == 1 \
		// 	|| cmd[i].in_red == 1)
		// 	{
		// 		printf("---____--> cmd[%d].fd_out ---> %d\n", i, cmd[i].fd_out);
		// 		printf("---____--> cmd[%d].fd_in ---> %d\n", i, cmd[i].fd_in);
		// 		//here_doc
		// 		printf("---____--> %d\n", cmd[i].here_doc);
				eof_counter = 0;
				while (cmd[i].eof[eof_counter] != NULL)
				{
					printf("cmd[%d].eof[%d] = %s\n", i, eof_counter,cmd[i].eof[eof_counter]);
					eof_counter++;
				}
			// }
		i++;
	}
}
