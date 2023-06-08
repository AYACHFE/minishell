/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:06:09 by rarraji           #+#    #+#             */
/*   Updated: 2023/06/08 18:29:34 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_error_2(t_minishell	*mini)
{
	int	i;

	i = 0;
	while (mini->cmd[i])
	{
		if (mini->cmd[i][0] == '|' && mini->cmd[i + 1] == NULL)
		{
			ft_putendl_fd("minishell: syntax error", 2);
			mini->exit_code = 2;
			return(1);
		}
		else if ((mini->cmd[i][0] == '"' && mini->cmd[i][1] == '"') && mini->cmd[i + 1][0] == '|')
		{
			ft_putendl_fd("minishell: command not found", 2);
			mini->exit_code = 0;
			return(1);
		}
		else if ((mini->cmd[i][0] == '\'' && mini->cmd[i][1] == '\'') && mini->cmd[i + 1][0] == '|')
		{
			ft_putendl_fd("minishell: command not found", 2);
			mini->exit_code = 0;
			return(1);
		}
		else if ((mini->cmd[i][0] == '>' && mini->cmd[i][1] == '>') && mini->cmd[i + 1][0] == '|')
		{
			ft_putendl_fd("minishell: syntax error", 2);
			mini->exit_code = 2;
			return(1);
		}
		else if (mini->cmd[i][0] == '>' && mini->cmd[i + 1][0] == '|')
		{
			ft_putendl_fd("minishell: syntax error", 2);
			mini->exit_code = 2;
			return(1);
		}
		else if (mini->cmd[i][0] == '<' && mini->cmd[i + 1][0] == '|')
		{
			ft_putendl_fd("minishell: syntax error", 2);
			mini->exit_code = 2;
			return(1);
		}
		else if (mini->cmd[i][0] == '|' && (mini->cmd[i + 1][0] == '"' && mini->cmd[i + 1][1] == '"'))
		{
			ft_putendl_fd("minishell: command not found", 2);
			mini->exit_code = 127;
			return(1);
		}
		else if (mini->cmd[i][0] == '|' && (mini->cmd[i + 1][0] == '\'' && mini->cmd[i + 1][1] == '\''))
		{
			ft_putendl_fd("minishell: command not found", 2);
			mini->exit_code = 127;
			return(1);
		}
		i++;
	}
	return (0);
}

int	check_first_cmd(char	*s)
{
	int i;

	i = 0;
	while (s[i] == 32)
		i++;
	if (s[i] == '"' && s[i + 1] == '"')
	{
		i += 2;
		while (s[i] == 32)
			i++;
		if (s[i] == '|')
		{
			ft_putendl_fd("minishell: command not found", 2);
			return (2);
		}
	}
	i = 0;
	while (s[i] == 32)
		i++;
	if (s[i] == '\'' && s[i + 1] == '\'')
	{
		i += 2;
		while (s[i] == 32)
			i++;
		if (s[i] == '|')
		{
			ft_putendl_fd("minishell: command not found", 2);
			return (2);
		}
	}
	return (1);
}

int ft_double_single_quote(char *str)
{
	int i;
	int j;
	int tmp;
	char c;

	i = 0;
	tmp = 1;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			tmp = 0;
			j = i + 1;
			c = str[i];
			while (str[j])
			{
				if (str[j] == c)
				{
					tmp = 1;
					break;
				}
				else
					j++;
			}
			i = j + 1;
		}
		else
			i++;
	}
	if (tmp == 0)
		printf("minishell: unexpected EOF while looking for matching\n");
		// printf("minishell: syntax error\n");
	return (tmp);
}

int	ft_error_pipe(char *s)
{
	int i;

	i = 0;
	if (check_first_cmd(s) == 2)
		return (2);
	i = 0;
	while (s[i] == '\"' || s[i] == '\'' || s[i] == ' ')
	{
		i++;
	}
	if (s[i] == '|')
	{
		printf("minishell: syntax error\n");
		return (0);
	}
	if (s[0] == '|' && s[1] == '\0')
	{
		printf("minishell: syntax error\n");
		return (0);
	}
	while (s[i])
	{
		if (s[i] == '|' && (s[i + 1] == '\0' || (s[i + 1] == '>' || (s[i + 1] == '>' && s[i + 2] == '>'))))
		{
			printf("minishell: syntax error\n");
			return (0);
		}
		if (s[i] == '|' && (s[i + 1] == '\0'))
		{
			printf("minishell: syntax error\n");
			return (0);
		}
		if (s[i] == '|' && s[i + 1] == ' ' && s[i + 2] == '|')
		{
			printf("minishell: syntax error\n");
			return (0);
		}
		if (s[i + 1] == '\0' && s[i] == '$')
		{
			printf("minishell: syntax error\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int ft_error_output(char *s, int l)
{
	int i;

	i = 0;
	if (s[0] == '>' && s[1] == '\0')
	{
		if (l == 1)
			printf("minishell: command not found\n");
		else
			printf("minishell: syntax error\n");
		return (0);
	}
	while (s[i])
	{
		if (s[i] == '>' && (s[i + 1] == '\0' || (s[i + 1] == '>' && s[i + 2] == '>') || (s[i + 1] == '<')))
		{
			if (l == 1)
				printf("minishell: command not found\n");
			else
				printf("minishell: syntax error\n");
			return (0);
		}
		if (s[i] == '>' && s[i + 1] == '\0')
		{
			if (l == 1)
				printf("minishell: command not found\n");
			else
				printf("minishell: syntax error\n");
			return (0);
		}
		i++;
	}
	return (1);
}
int ft_error_input(char *s, int l)
{
	int i;

	i = 0;
	if (s[0] == '<' && s[1] == '\0')
	{
		if (l == 1)
			printf("minishell: command not found\n");
		else
			printf("minishell: syntax error\n");
		return (0);
	}
	while (s[i])
	{
		if (s[i] == '<' && (s[i + 1] == '\0' || (s[i + 1] == '|' || (s[i + 1] == '<' && s[i + 2] == '<'))))
		{
			if (l == 1)
				printf("minishell: command not found\n");
			else
				printf("minishell: syntax error\n");
			return (0);
		}
		if (s[i] == '<' && s[i + 1] == '\0')
		{
			if (l == 1)
				printf("minishell: command not found\n");
			else
				printf("minishell: syntax error\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int ft_error_appends(char *s, int l)
{
	int i;

	i = 0;
	if (s[0] == '>' && s[1] == '>' && s[2] == '\0')
	{
		if (l == 1)
			printf("minishell: command not found\n");
		else
			printf("minishell: syntax error\n");
		return (0);
	}
	while (s[i])
	{
		if ((s[i] == '>' && s[i + 1] == '>') && (s[i + 2] == '\0' || (s[i + 2] == '|' || (s[i + 1] == '>' && s[i + 2] == '<'))))
		{
			if (l == 1)
				printf("minishell: command not found\n");
			else
				printf("minishell: syntax error\n");
			return (0);
		}
		if (s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '\0')
		{
			if (l == 1)
				printf("minishell: command not found\n");
			else
				printf("minishell: syntax error\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int ft_error_here_document(char *s, int l)
{
	int i;

	i = 0;
	if (s[0] == '<' && s[1] == '<' && s[2] == '\0')
	{
		if (l == 1)
			printf("minishell: command not found\n");
		else
			printf("minishell: syntax error\n");
		return (0);
	}
	if (s[i] == '<' && s[i + 1] == '<')
	{
		i = i + 2;
		while (s[i] == ' ')
			i++;
		if (s[i] == '|')
		{
			if (l == 1)
				printf("minishell: command not found\n");
			else
				printf("minishell: syntax error\n");
			return (0);
		}
	}
	i = 0;
	while (s[i])
	{
		if ((s[i] == '<' && s[i + 1] == '<') && (s[i + 2] == '\0' || (s[i + 2] == '|' || (s[i + 1] == '>' && s[i + 2] == '<'))))
		{
			if (l == 1)
				printf("minishell: command not found\n");
			else
				printf("minishell: syntax error\n");
			return (0);
		}
		if (s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '\0')
		{
			if (l == 1)
				printf("minishell: command not found\n");
			else
				printf("minishell: syntax error\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int ft_error(char *str, int i)
{
	int	ret;

	ret = ft_error_pipe(str);
	if (ret == 2)
		return (2);
	if (ret == 0)
		return (0);
	if (ft_double_single_quote(str) == 0)
		return (0);
	if (ft_error_appends(str, i) == 0)
		return (0);
	if (ft_error_here_document(str, i) == 0)
		return (0);
	if (ft_error_output(str, i) == 0)
		return (0);
	if (ft_error_input(str, i) == 0)
		return (0);
	return (1);
}
