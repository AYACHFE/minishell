/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:50:16 by rarraji           #+#    #+#             */
/*   Updated: 2023/05/26 15:50:18 by rarraji          ###   ########.fr       */
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
		// else if (mini->cmd[i][0] == '>')
		// 	counter++;
		// else if (mini->cmd[i][0] == '<')
		// 	counter++;
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
	
	l = 0;
	k = 0;
	j = 0;
	i = 0;
	while (i < general_info->cmd_nb)
	{
		check = 0;
		k = 0;
		l = 0;

			cmd[i].args = malloc(sizeof(char *) * 10);
			cmd[i].fd_in = 0;
			cmd[i].fd_out = 1;
			while (general_info->str[j] && (general_info->str[j][0] != '|'))
			{
				//this part is for redirection
				if (general_info->str[j][0] == '>' || general_info->str[j][0] == '<')
				{
					if (general_info->str[j + 1] != NULL && (general_info->str[j][0] == '>' && general_info->str[j][1] == '>'))
					{
						cmd[i].append = 1;
						cmd[i].append_file = general_info->str[++j];
						cmd[i].fd_out = (open(general_info->str[j], O_RDWR | O_CREAT, 0660));
						if (cmd[i].fd_out == -1)
						{
							perror("open");
							return ;
						}
					}
					else if (general_info->str[j + 1] != NULL && (general_info->str[j][0] == '>'))
					{
						cmd[i].out_red = 1;
						cmd[i].out_red_file = general_info->str[++j];
						cmd[i].fd_out = (open(general_info->str[j], O_RDWR | O_CREAT, 0660));
						if (cmd[i].fd_out == -1)
						{
							perror("open");
							return ;
						}
					}
					else if (general_info->str[j + 1] != NULL && (general_info->str[j][0] == '<' && general_info->str[j][1] == '<'))
					{
						//here_doc
						cmd[i].here_doc = 1;
						cmd[i].here_doc_file = general_info->str[++j];
					}
					else if (general_info->str[j + 1] != NULL && (general_info->str[j][0] == '<'))
					{
						cmd[i].in_red = 1;
						cmd[i].in_red_file = general_info->str[++j];
						if (access(general_info->str[j], F_OK) != 0)
						{
							perror(general_info->str[j]);
							return ;
						}
						cmd[i].fd_in = open(general_info->str[j], O_RDONLY);
					}
				}
				//this part is for normal cmd with or whithout a pipe
				else if (general_info->str[j])
				{
					cmd[i].args[l] = ft_strdup(general_info->str[j]);
					l++;
				}
				if (general_info->str[j + 1] == NULL)
				{
					break ;
				}
				j++;
				k++;
			}
			cmd[i].args[l] = NULL;
			cmd[i].general_info = general_info;
			j++;
			i++;
	}
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
		printf("-----\n");
		if (cmd[i].append == 1 || cmd[i].here_doc == 1 || cmd[i].out_red == 1 \
		|| cmd[i].in_red == 1)
		{
			printf("---____--> cmd[%d].fd_out ---> %d\n", i, cmd[i].fd_out);
			printf("---____--> cmd[%d].fd_in ---> %d\n", i, cmd[i].fd_in);
			printf("---____--> %d, append_file-> %s\n", cmd[i].append, cmd[i].append_file);
			printf("---____--> %d, here_doc_file-> %s\n", cmd[i].here_doc, cmd[i].here_doc_file);
			printf("---____--> %d, out_red_file-> %s\n", cmd[i].out_red, cmd[i].out_red_file);
			printf("---____--> %d, in_red_file-> %s\n", cmd[i].in_red, cmd[i].in_red_file);
		}
		printf("-----\n");
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

	to_struct_2(cmd, general_info);
}