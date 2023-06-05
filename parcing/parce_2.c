/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:54:44 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/05 12:55:13 by aachfenn         ###   ########.fr       */
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
	tab = malloc(sizeof(int) * general_info->cmd_nb + 1);
	while (general_info->str[i])
	{
		j = 0;
		while (general_info->str[i][0] != '|')
		{
			if (general_info->str[i][0] == '<' || general_info->str[i][0] == '>')
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
	tab[k] = '\0';
	return (tab);
}

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
		i++;
	}
	return (counter + 1);
}

//this function should be removed after its just helps to debug
void	print_all_data(t_cmd	*cmd, t_cmd_info	*general_info)
{
	//prints all the struct data , and the data is about the cmds
	int	i;
	int	j;
	int	eof_counter;
	int	fl;
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
		fl = 0;
		while (cmd[i].files[fl])
		{
			printf("cmd[%d].files[%d] == %s\n", i, fl, cmd[i].files[fl]);
			fl++;
		}
			if (cmd[i].append == 1 || cmd[i].here_doc == 1 || cmd[i].out_red == 1 \
			|| cmd[i].in_red == 1)
			{
				printf("---____--> cmd[%d].fd_out ---> %d\n", i, cmd[i].fd_out);
				printf("---____--> cmd[%d].fd_in ---> %d\n", i, cmd[i].fd_in);
				//here_doc
				printf("---____--> %d\n", cmd[i].here_doc);
				eof_counter = 0;
				while (cmd[i].eof[eof_counter] != NULL)
				{
					printf("cmd[%d].eof[%d] = %s\n", i, eof_counter,cmd[i].eof[eof_counter]);
					eof_counter++;
				}
			}
		printf("-----\n");
		i++;
	}
}

void	tokens_redirection(t_cmd	*cmd, t_cmd_info	*general_info, int j, int eof_counter, int fl)
{
	if (general_info->str[j + 1] != NULL && (general_info->str[j][0] == '>' && general_info->str[j][1] == '>'))
	{
		//append >>
		cmd->append = 1;
		// general_info->files[fl] = ft_strjoin(">>", general_info->str[j]);
		// cmd->append_file = general_info->str[j];
		cmd->files[fl] = ft_strjoin(">>", general_info->str[++j]);
		fl++;
		//
		// cmd->fd_out = (open(general_info->str[j], O_RDWR | O_CREAT | O_APPEND, 0660));
		// if (cmd->fd_out == -1)
		// {
		// 	perror("open");
		// 	return ;
		// }
	}
	else if (general_info->str[j + 1] != NULL && (general_info->str[j][0] == '>'))
	{
		//out_redirection
		cmd->out_red = 1;
		// cmd->out_red_file = general_info->str[++j];
		// general_info->files[fl] = ft_strjoin("> ", general_info->str[j]);
		cmd->files[fl] = ft_strjoin("> ", general_info->str[++j]);
		fl++;
		//
		// cmd->fd_out = (open(general_info->str[j], O_RDWR | O_CREAT, 0660));
		// if (cmd->fd_out == -1)
		// {
		// 	perror("open");
		// 	return ;
		// }
	}
	else if (general_info->str[j + 1] != NULL && (general_info->str[j][0] == '<' && general_info->str[j][1] == '<'))
	{
		//here_doc
		cmd->here_doc = 1;
		cmd->eof[eof_counter] = ft_strdup(general_info->str[++j]);
		// general_info->eof[eof_counter] = ft_strdup(general_info->str[j]);
		cmd->eof[++eof_counter] = NULL;
		// general_info->eof[eof_counter] = NULL;
	}
	else if (general_info->str[j + 1] != NULL && (general_info->str[j][0] == '<'))
	{
		//in_redirection
		cmd->in_red = 1;
		// cmd->in_red_file = general_info->str[++j];
		// general_info->files[fl] = ft_strjoin("< ", general_info->str[j]);
		cmd->files[fl] = ft_strjoin("< ", general_info->str[j]);
		fl++;
		//
		// if (access(general_info->str[j], F_OK) != 0)
		// {
		// 	perror(general_info->str[j]);
		// 	break ;
		// }
		// cmd->fd_in = open(general_info->str[j], O_RDONLY);
	}
}

void	to_struct_2(t_cmd	*cmd, t_cmd_info	*general_info)
{
	int	i;
	int	j;
	int	l;
	int	eof_counter;
	int	*tab;
	int	fl;
	
	l = 0;
	j = 0;
	i = 0;
	fl = 0;
	tab = args_counter(general_info);
	while (i < general_info->cmd_nb)
	{
		eof_counter = 0;
		// k = 0;
		l = 0;
		fl = 0;
			cmd[i].args = malloc(sizeof(char *) * tab[i] + 1);
			cmd[i].files = malloc(sizeof(char * ) * general_info->files_nb);
			cmd[i].eof = malloc(sizeof(char *) * general_info->here_doc_nb + 1);
			cmd[i].fd_in = 0;
			cmd[i].fd_out = 1;
			//////////
			cmd[i].append = 0;
			cmd[i].out_red = 0;
			cmd[i].out_red = 0;
			cmd[i].here_doc = 0;
			while (general_info->str[j] && (general_info->str[j][0] != '|'))
			{
				//this part is for redirection
				if (general_info->str[j][0] == '>' || general_info->str[j][0] == '<')
				{
					// tokens_redirection(&cmd[i], general_info, j, eof_counter, fl);
					if (general_info->str[j + 1] != NULL && (general_info->str[j][0] == '>' && general_info->str[j][1] == '>'))
					{
						//append >>
						cmd[i].append = 1;
						cmd[i].files[fl] = ft_strjoin(">>", general_info->str[++j]);
						fl++;
					}
					else if (general_info->str[j + 1] != NULL && (general_info->str[j][0] == '>'))
					{
						//out_redirection
						cmd[i].out_red = 1;
						cmd[i].files[fl] = ft_strjoin("> ", general_info->str[++j]);
						fl++;
					}
					else if (general_info->str[j + 1] != NULL && (general_info->str[j][0] == '<' && general_info->str[j][1] == '<'))
					{
						//here_doc
						cmd[i].here_doc = 1;
						cmd[i].eof[eof_counter] = ft_strdup(general_info->str[++j]);
						cmd[i].eof[++eof_counter] = NULL;
					}
					else if (general_info->str[j + 1] != NULL && (general_info->str[j][0] == '<'))
					{
						//in_redirection
						cmd[i].in_red = 1;
						cmd[i].files[fl] = ft_strjoin("< ", general_info->str[++j]);
						fl++;
					}
				}
				//this part is for normal cmd with or whithout a pipe
				else if (general_info->str[j])
				{
					cmd[i].args[l] = ft_strdup(general_info->str[j]);
					l++;
				}
				cmd[i].args[l] = NULL;
				j++;
			}
			cmd[i].general_info = general_info;
			cmd[i].files[fl] = NULL;
			j++;
			i++;
	}
	//////////
	// print_all_data(cmd, general_info);
}

void	to_struct(t_minishell	*mini, t_cmd	*cmd)
{
	int	i;
	t_cmd_info	*general_info;

	i = 0;
	//init the struct 
	general_info = malloc(sizeof(t_cmd_info));
	general_info->cmd_nb = cmd_counter(mini);
	general_info->pipe_nb = 0;
	general_info->append_nb = 0;
	general_info->here_doc_nb = 0;
	general_info->in_red_nb = 0;
	general_info->out_red_nb = 0;
	general_info->str = mini->tmp_cmd;
	general_info->exit_code = 0;

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
	general_info->files_nb = general_info->append_nb + general_info->out_red_nb + general_info->in_red_nb;
	// printf("files_nb ----> %d\n", general_info->files_nb);
	// int	*tab;
	// tab = args_counter(general_info);
	// i = 0;
	// while (tab[i])
	// {
	// 	printf("tab[%d] == %d\n", i, tab[i]);
	// 	i++;
	// }
	// printf("cmd_counter == %d\n", general_info->cmd_nb);
	// printf("general_info->pipe_nb == %d\n", general_info->pipe_nb);
	// printf("general_info->append_nb == %d\n", general_info->append_nb);
	// printf("general_info->here_doc_nb == %d\n", general_info->here_doc_nb);
	// printf("general_info->in_red_nb == %d\n", general_info->in_red_nb);
	// printf("general_info->out_red_nb == %d\n", general_info->out_red_nb);
	to_struct_2(cmd, general_info);
}
