/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:41:45 by rarraji           #+#    #+#             */
/*   Updated: 2023/06/17 20:19:56 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup1(char *s1)
{
	char	*ss1;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (s1[++i])
	{
		if(s1[i] == '\"')
			j++;
	}
	ss1 = malloc(((i - j) + 1) * (sizeof(char)));
	if (!ss1)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		if(s1[i] == '\"')
			i++;
		else
			ss1[j++] = s1[i++];
	}
	ss1[j] = '\0';
	return (ss1);
}

int check_valid_exp(char *arg, int check)
{
	int i;

	i = 0;
	while(arg[i] != '=' && arg[i])
	{
		if(ft_isdigit(arg[0]) == 1)
		{
			if(check == 1)
				ft_putendl_fd("minishell: not a valid identifier", 2);
			return(0);
		}
		i++;
	}

	return(1);
}

void	ft_export_ext_1(t_cmd	*cmd, int *i, int *t)
{
	int	j;

	j = 0;
	if(cmd->args[2] == '\0')
		*t = 0;
	else
	{	
		while(cmd->args[*i])
		{
			j = *i + 1;
			while(cmd->args[j])
			{
				if(ft_strncmp(cmd->args[*i], cmd->args[j], ft_strlen(cmd->args[*i])) == 0)
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

void	ft_export_ext_2__(t_cmd	*cmd, char	**arg, int *i, int *t)
{
	int	j;

	j = *i + 1;
	while(cmd->args[j])
	{
		if(ft_strncmp(cmd->args[*i], cmd->args[j], ft_strlen(cmd->args[*i])) == 0)
			break;
		else
			j++;
	}
	if(cmd->args[j] == '\0')
		arg[(*t)++] = cmd->args[*i];
}

void	ft_export_ext_2(t_cmd	*cmd, char	**arg)
{
	int i;
	int	j;
	int	t;

	i = 1;
	j = 0;
	t = 0;
	if(cmd->args[i + 1] == '\0')
		arg[t++] = cmd->args[i];
	else
	{
		while(cmd->args[i])
		{
			ft_export_ext_2__(cmd, arg, &i, &t);
			i++;
		}
	}
	arg[t] = NULL;
}

void	ft_export_ext_3(t_minishell	*mini, char	**arg, int	*t)
{
	int	i;

	i = 0;
	while(arg[i])
	{
		if(check_valid_exp(arg[i], 1) == 1)
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
	int i;
	int	t;
	char **arg;

	i = 1;
	t = 0;
	ft_export_ext_1(cmd, &i, &t);
	arg = malloc((i - t + 1) * (sizeof(char *)));
	ft_export_ext_2(cmd, arg);
	t = 0;
	ft_export_ext_3(mini, arg, &t);
	if (cmd->args[1])
	{
		ft_rem_var(arg ,mini, t);
		ft_rem_var_export(arg ,mini, t);
	}
	else
		print_export(mini);
}

int	ft_check_var_exect_ext(t_minishell	*mini, char	*s)
{
	int	i;
	int	j;
	int	d;

	i = 0;
	j = 0;
	d = 11;
	while (mini->my_export[i])
	{
		while (mini->my_export[i][d] == s[j] && s[j] != '=' && mini->my_export[i][d] != '\0' && s[j] != '\0')
		{
			j++;
			d++;
		}
		if((mini->my_export[i][d] == '=' || mini->my_export[i][d] == '\0') && (s[j] == '=' || s[j] == '\0'))
			return (i);
		else
		{
			d = 11;
			j = 0;	
		}
		i++;
	}
	return (0);
}

int	ft_check_var_exect(char *s,t_minishell *mini, int var)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	if (var == 0)
	{
		if (ft_check_var_exect_ext(mini, s) != 0)
			return (ft_check_var_exect_ext(mini, s));
	}
	else
	{
		while (mini->my_env[i])
		{
			while (mini->my_env[i][j] == s[j] && s[j] != '=')
				j++;
			if (mini->my_env[i][j] == '=' && s[j] == '=')
				return (i);
			else
				j = 0;	
			i++;
		}
	}
	return (0);
}

void	ft_rem_var_ext_1(t_minishell	*mini, char	**str, char	**my_tmp)
{
	int	i;
	int	j;
	int	d;

	i = -1;
	j = 0;
	d = 0;
	while (str[++i])
	{
		if (ft_check_var_exect(str[i], mini, 0) != 0)
			rem_var_env(mini, ft_check_var_exect(str[i], mini, 1));
	}
	while (mini->my_env[d])
		my_tmp[j++] = ft_strdup(mini->my_env[d++]);
	d = j;
	i = 0;
	j = 0;
	while(str[i] && (ft_strchr(str[i], '=') != NULL))
	{
		if(check_valid_exp(str[i], 0) == 0)
			i++;
		else
			my_tmp[d++] = ft_strdup1(str[i++]);
	}
	my_tmp[d] = NULL;
}

void	ft_rem_var(char **str, t_minishell *mini, int	t)
{
	char **my_tmp;
	int i;
	int j;

	i = 0;
	j = 0;
	while (mini->my_env[j])
		j++;	
	my_tmp = malloc(sizeof(char *) * (j + t + 1)); 
	ft_rem_var_ext_1(mini, str, my_tmp);
	i = 0;
	while (mini->my_env[i]) 
	{
		free(mini->my_env[i]);
		i++;
	}
	mini->my_env = my_tmp;
}

void	ft_add_double_ext_1(char	*s, char	*str, int	*i, int	*tmp)
{
	int	j;

	j = 0;
	while (s[j])
	{
		str[*i] = s[j];
		if((ft_strchr(s, '=') != NULL) && (s[j] == '=' && s[j + 1] == '\0'))
		{
			str[++(*i)] = '\"';
			str[++(*i)] = '\"';
			return ;
		}
		else if (ft_strchr(s, '=') != NULL && s[j] == '=' && *tmp == 0)
		{
			str[++(*i)] = '\"';		
			*tmp = 1;
		}
		(*i)++;
		j++;
	}
	if(s[j] == '\0' && ft_strchr(s, '=') != NULL)
		str[(*i)] = '\"';
	str[++(*i)] = '\0';
}

char *ft_add_double(char *s)
{
	char	dec[12] ="declare -x ";
	char	*str;
	int		i;
	int		j;
	int		tmp;

	tmp = 0;
	i = 0;
	j = 0;
	while(s[i])
		i++;
	str = malloc(i + 14);
	if (!str)
		return (0);
	i = 0;
	while(dec[i])
	{
		str[i] = dec[i];
		i++;
	}
	ft_add_double_ext_1(s, str, &i, &tmp);
	free(s);
	return (str);
}

void	ft_rem_var_export_ext(char	**str, char	**my_tmp, int	*n)
{
	int	i;

	i = 0;
	while(str[i])
	{

		if(check_valid_exp(str[i], 0) == 0)
			i++;
		else
		{
			my_tmp[*n] = ft_strdup1(str[i]);
			my_tmp[*n] = ft_add_double(my_tmp[*n]);
			(*n)++;
			i++;
		}
	}
	my_tmp[*n] = NULL;
}

void	ft_rem_var_export_ext_1(t_minishell	*mini, char	**str, char	**my_tmp, int	*n)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (str[i])
	{
		if(ft_check_var_exect(str[i], mini, 0) != 0)
			search_in_export(mini, str[i]);
		i++;
	}
	while (mini->my_export[d])
	{
		my_tmp[*n] = ft_strdup(mini->my_export[d]);
		(*n)++;
		d++;
	}
}

void	ft_rem_var_export(char **str, t_minishell *mini, int t)
{
	char **my_tmp;
	int	j;
	int n;

	n = 0;
	j = 0;
	while (mini->my_export[j])
		j++;
	my_tmp = malloc(sizeof(char *) * (j + t + 1)); 	
	ft_rem_var_export_ext_1(mini, str, my_tmp, &n);
	ft_rem_var_export_ext(str, my_tmp, &n);
	j = 0;
	while (mini->my_export[j]) 
		free(mini->my_export[j++]);
	mini->my_export = my_tmp;
}

void	print_export(t_minishell *mini)
{
	int	j;

	j = 0;
	while(mini->my_export[j])
	{
		printf("%s\n", mini->my_export[j]);
		j++;
	}
}
