/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:54:44 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/01 11:49:15 by aachfenn         ###   ########.fr       */
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

void	to_struct_2(t_cmd	*cmd, t_cmd_info	*general_info)
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	check;
	int	eof_counter;
	int	*tab;
	int	fl;
	
	l = 0;
	k = 0;
	j = 0;
	i = 0;
	fl = 0;
	tab = args_counter(general_info);
	general_info->files = malloc(sizeof(char *) * general_info->files_nb + 1);
	general_info->eof = malloc(sizeof(char *) * general_info->here_doc_nb + 1);
	// eof_counter = 0;
	while (i < general_info->cmd_nb)
	{
		eof_counter = 0;
		check = 0;
		k = 0;
		l = 0;
			cmd[i].args = malloc(sizeof(char *) * tab[i] + 1);
			// cmd[i].args = malloc(sizeof(char *) * 10);
			// printf("tab[%d] --> %d\n", i, tab[i]);
			// cmd[i].eof = malloc(sizeof(char *) * 10);
			cmd[i].eof = malloc(sizeof(char *) * general_info->here_doc_nb + 1);
			cmd[i].fd_in = 0;
			cmd[i].fd_out = 1;
			//////////
			cmd[i].append_file = NULL;
			cmd[i].out_red_file = NULL;
			cmd[i].out_red_file = NULL;
			// cmd[i].here_doc_file = NULL;
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
					if (general_info->str[j + 1] != NULL && (general_info->str[j][0] == '>' && general_info->str[j][1] == '>'))
					{
						//append >>
						cmd[i].append = 1;
						cmd[i].append_file = general_info->str[++j];
						general_info->files[fl++] = ft_strjoin(">>", general_info->str[j]);
						// cmd[i].fd_out = (open(general_info->str[j], O_RDWR | O_CREAT | O_APPEND, 0660));
						// if (cmd[i].fd_out == -1)
						// {
						// 	perror("open");
						// 	return ;
						// }
					}
					else if (general_info->str[j + 1] != NULL && (general_info->str[j][0] == '>'))
					{
						//out_redirection
						cmd[i].out_red = 1;
						cmd[i].out_red_file = general_info->str[++j];
						general_info->files[fl++] = ft_strjoin("> ", general_info->str[j]);
						//
						// cmd[i].fd_out = (open(general_info->str[j], O_RDWR | O_CREAT, 0660));
						// if (cmd[i].fd_out == -1)
						// {
						// 	perror("open");
						// 	return ;
						// }
					}
					else if (general_info->str[j + 1] != NULL && (general_info->str[j][0] == '<' && general_info->str[j][1] == '<'))
					{
						//here_doc
						cmd[i].here_doc = 1;
						cmd[i].eof[eof_counter] = ft_strdup(general_info->str[++j]);
						general_info->eof[eof_counter] = ft_strdup(general_info->str[j]);
						cmd[i].eof[++eof_counter] = NULL;
						general_info->eof[eof_counter] = NULL;
					}
					else if (general_info->str[j + 1] != NULL && (general_info->str[j][0] == '<'))
					{
						//in_redirection
						cmd[i].in_red = 1;
						cmd[i].in_red_file = general_info->str[++j];
						general_info->files[fl++] = ft_strjoin("< ", general_info->str[j]);
						//
						// if (access(general_info->str[j], F_OK) != 0)
						// {
						// 	perror(general_info->str[j]);
						// 	break ;
						// }
						// cmd[i].fd_in = open(general_info->str[j], O_RDONLY);
					}
				}
				//this part is for normal cmd with or whithout a pipe
				else if (general_info->str[j])
				{
					// puts("-args--->");
					cmd[i].args[l] = ft_strdup(general_info->str[j]);
					l++;
				}
				if (general_info->str[j + 1] == NULL)
				{
					break ;
				}
				cmd[i].args[l] = NULL;
				j++;
				k++;
			}
			general_info->files[fl] = NULL;
			cmd[i].general_info = general_info;
			j++;
			i++;
	}
	// //prints all the struct data , and the data is about the cmds
	i = 0;
	j = 0;
	
	// fl = 0;
	// while (fl < general_info->files_nb)
	// {
	// 	printf("general_info->files[%d] == %s\n", fl, general_info->files[fl]);
	// 	fl++;
	// }
	
	// while (i < general_info->cmd_nb)
	// {
	// 	l = 0;
	// 	while (cmd[i].args[l] != NULL)
	// 	{
	// 		printf("--->cmd[%d].args[%d]--> %s\n",i, l, cmd[i].args[l]);
	// 		l++;
	// 	}
	// 	if (cmd[i].append == 1 || cmd[i].here_doc == 1 || cmd[i].out_red == 1 \
	// 	|| cmd[i].in_red == 1)
	// 	{
	// 		printf("---____--> cmd[%d].fd_out ---> %d\n", i, cmd[i].fd_out);
	// 		printf("---____--> cmd[%d].fd_in ---> %d\n", i, cmd[i].fd_in);
	// 		printf("---____--> %d, append_file-> %s\n", cmd[i].append, cmd[i].append_file);
	// 		//here_doc
			// eof_counter = 0;
			// while (cmd[i].eof[eof_counter] != NULL)
			// {
			// 	printf("cmd[%d].eof[%d] = %s\n", i, eof_counter,cmd[i].eof[eof_counter]);
			// 	eof_counter++;
			// 	// printf("cmd[%d].eof[%d] = %s\n", i, eof_counter,cmd[i].eof[eof_counter]);
			// }
	// 		printf("---____--> %d, out_red_file-> %s\n", cmd[i].out_red, cmd[i].out_red_file);
	// 		printf("---____--> %d, here_doc-> %d\n", cmd[i].here_doc, cmd[i].here_doc);
	// 		printf("---____--> %d, in_red_file-> %s\n", cmd[i].in_red, cmd[i].in_red_file);
	// 	}
	// 	printf("-----\n");
	// 	i++;
	// }
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
	printf("files_nb ----> %d\n", general_info->files_nb);
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
