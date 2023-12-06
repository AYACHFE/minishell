/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:32:37 by rarraji           #+#    #+#             */
/*   Updated: 2023/06/19 10:47:49 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_count_arg_valid(t_cmd	*cmd, int *i, int *t)
{
	int	j;

	j = 0;
	if (cmd->args[2] == '\0')
		*t = 0;
	else
	{	
		while (cmd->args[*i])
		{
			j = *i + 1;
			while (cmd->args[j])
			{
				if (ft_strncmp(cmd->args[*i], cmd->args[j], \
				ft_strlen(cmd->args[*i])) == 0)
				{
					(*t)++;
					break ;
				}
				else
					j++;
			}
			(*i)++;
		}
	}	
}

void	ft_remplir_arg__(t_cmd	*cmd, char	**arg, int *i, int *t)
{
	int	j;

	j = *i + 1;
	while (cmd->args[j])
	{
		if (ft_strncmp(cmd->args[*i], cmd->args[j], \
		ft_strlen(cmd->args[*i])) == 0)
			break ;
		else
			j++;
	}
	if (cmd->args[j] == '\0')
		arg[(*t)++] = cmd->args[*i];
}

void	ft_remplir_arg(t_cmd	*cmd, char	**arg)
{
	int	i;
	int	j;
	int	t;

	i = 1;
	j = 0;
	t = 0;
	if (cmd->args[i + 1] == '\0')
		arg[t++] = cmd->args[i];
	else
	{
		while (cmd->args[i])
		{
			ft_remplir_arg__(cmd, arg, &i, &t);
			i++;
		}
	}
	arg[t] = NULL;
}

void	check_valid_identifier(t_minishell	*mini, char	**arg, int	*t)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (check_valid_exp(arg[i], 1) == 1)
		{
			(*t)++;
			i++;
		}
		else
		{
			mini->exit_code = 1;
			i++;
		}
	}
}

void	ft_export(t_cmd	*cmd, t_minishell *mini)
{
	int		i;
	int		t;
	char	**arg;

	i = 1;
	t = 0;
	ft_count_arg_valid(cmd, &i, &t);
	arg = malloc((i - t + 1) * (sizeof(char *)));
	ft_remplir_arg(cmd, arg);
	t = 0;
	check_valid_identifier(mini, arg, &t);
	if (cmd->args[1])
	{
		add_var_env(arg, mini, t);
		add_var_export(arg, mini, t);
		free(arg);
	}
	else
		print_export(mini);
}
