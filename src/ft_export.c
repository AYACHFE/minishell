/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:41:45 by rarraji           #+#    #+#             */
/*   Updated: 2023/06/10 21:56:01 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup1(char *s1)
{
	int		i;
	int		j;
	char	*ss1;

	i = 0;
	j = 0;
	while (s1[i])
	{
		if(s1[i] == '\"')
			j++;
		i++;
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
		{
			ss1[j] = s1[i];
			j++;
			i++;
		}
			
	}
	ss1[j] = '\0';
	return (ss1);
}

int check_valid_exp(char *arg, int check)
{
	int i;
	// int l;
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

void	ft_export(t_cmd	*cmd, t_minishell *mini)
{
	
	int i = 1;
	int	j = 0;
	int	t = 0;
	int	check = 1;
	char **arg;


	// printf("--==%s\n", cmd->args[i]);
	if(cmd->args[2] == '\0')
		t = 0;
	else
	{	
		while(cmd->args[i])
		{
			j = i + 1;
			while(cmd->args[j])
			{
				if(ft_strncmp(cmd->args[i], cmd->args[j], ft_strlen(cmd->args[i])) == 0)
				{
					t++;
					break;
				}
				else
					j++;	
			}
			i++;
		}
	}	
	arg = malloc((i - t + 1) * (sizeof(char *)));
	i = 1;
	j = 0;
	t = 0;
	if(cmd->args[i + 1] == '\0')
	{
		arg[t] = cmd->args[i];
		t++;
	}
	else
	{
		while(cmd->args[i])
		{
			j = i + 1;
			while(cmd->args[j])
			{
				if(ft_strncmp(cmd->args[i], cmd->args[j], ft_strlen(cmd->args[i])) == 0)
					break;
				else
					j++;
			}
			if(cmd->args[j] == '\0')
			{
				arg[t] = cmd->args[i];
				t++;
			}	
			i++;
		}
	}	
	arg[t] = NULL;
	// i = check_valid_exp(arg , 0);
	// if (i == 0)
	// 	mini->exit_code = 1;
	// t = 0;
	// while(arg[t])
	// {
	// 	 printf("-------->%s\n", arg[t]);
	// 	 t++;
	// }
	i = 0;
	t = 0;
	while(arg[i])
	{
		if(check_valid_exp(arg[i], check) == 1)
		{
			t++;
			i++;
		}
		else
		{
			mini->exit_code = 1;
			i++;
		}
	}
	if (cmd->args[1])
	{
		ft_rem_var(arg ,mini, t);
		ft_rem_var_export(arg ,mini, t);
	}
	else
		print_export(mini);
}

int	ft_check_var_exect(char *s,t_minishell *mini, int var)
{
	int i;
	int	j;
	int	d;

	i = 0;
	j = 0;
	d = 11;
	// printf("****%s\n", s);
	if (var == 0)
	{	
		while (mini->my_export[i])
		{
			// i = tmp;
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
	}
	else
	{
		while (mini->my_env[i])
		{
			// i = tmp;
			while (mini->my_env[i][j] == s[j] && s[j] != '=')
				j++;
			if(mini->my_env[i][j] == '=' && s[j] == '=')
				return (i);
			else
				j = 0;	
			i++;
		}
	}
	return (0);
}


void	ft_rem_var(char **str, t_minishell *mini, int	t)
{
	int i = 0;
	int	check = 0;
	int j;
	int d;
	int n;
	char **my_tmp;
	
	// printf("***%s\n", str[i]);
	j = 0;
	n = 0;
	while (mini->my_env[j])
		j++;
		
	my_tmp = malloc(sizeof(char *) * (j + t + 1)); 
	d = 0;
	j = 0;
	i = 0;
	while (str[i])
	{
		if (ft_check_var_exect(str[i], mini, 0) != 0)
			rem_var_env(mini, ft_check_var_exect(str[i], mini, 1));
		i++;
	}
	while (mini->my_env[d])
	{
		my_tmp[n] = ft_strdup(mini->my_env[d]);
		n++;
		d++;
	}
	i = 0;
	j = 0;
	while(str[i] && (ft_strchr(str[i], '=') != NULL))
	{
		// if(ft_check_var_exect(str[i], mini, 0) != 0)
		// {
		// 	puts("reda");
		// 	ft_unset(cmd ,mini);
		// }
		// printf("***%s\n", str[i]);
		if(check_valid_exp(str[i], check) == 0)
			i++;
		else
		{
			my_tmp[n] = ft_strdup1(str[i]);
			// printf("env=%d------>%s\n", i, str[i]);
			// printf("env=%d------>%s\n", n, my_tmp[n]);
			// printf("--------------\n");
			n++;
			i++;
		}
	}
	my_tmp[n] = NULL;
	i = 0;
	while (mini->my_env[i]) 
	{
		free(mini->my_env[i]);
		i++;
	}
	j = 0;
    // while(my_tmp[j])
    // {
    //     printf("%d------>%s\n", j, my_tmp[j]);
    //     j++;
    // }
	mini->my_env = my_tmp;
}

char *ft_add_double(char *s)
{
	int		i;
	int		j;
	char *str;
	int tmp = 0;
	char dec[12] ="declare -x ";

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
	while (s[j])
	{
		str[i] = s[j];
		if((ft_strchr(s, '=') != NULL) && (s[j] == '=' && s[j + 1] == '\0'))
		{
			str[++i] = '\"';
			str[++i] = '\"';
			return (str);
		}
		else if (ft_strchr(s, '=') != NULL && s[j] == '=' && tmp == 0)
		{
			str[++i] = '\"';		
			tmp = 1;
		}
		i++;
		j++;
	}
	if(s[j] == '\0' && ft_strchr(s, '=') != NULL)
		str[i] = '\"';
	str[++i] = '\0';
	free(s);
	return (str);
}

void	ft_rem_var_export(char **str, t_minishell *mini, int t) // add_variable
{
	int i = 0;
	int j;
	int d;
	int n;
	int	check = 0;
	char **my_tmp;

	j = 0;
	n = 0;
	while (mini->my_export[j])
		j++;
	my_tmp = malloc(sizeof(char *) * (j + t + 1)); 	
	d = 0;
	j = 0;
	i = 0;
	while (str[i])
	{
		if(ft_check_var_exect(str[i], mini, 0) != 0)
			search_in_export(mini, str[i]);
		i++;
	}
	while (mini->my_export[d])
	{
		my_tmp[n] = ft_strdup(mini->my_export[d]);
		n++;
		d++;
	}
	i = 0;
	while(str[i])
	{
		// if(ft_check_var_exect(str[i], mini, 0) != 0)
		// {
		// 	puts("reda");
		// 	ft_unset(cmd ,mini);
		// }
		// printf("***%s\n", str[i]);
		if(check_valid_exp(str[i], check) == 0)
			i++;
		else
		{
			my_tmp[n] = ft_strdup1(str[i]);
			my_tmp[n] = ft_add_double(my_tmp[n]);
			// printf("exp=%d------>%s\n", i, str[i]);
			// printf("exp=%d------>%s\n", n, my_tmp[n]);
			// printf("--------------\n");
			n++;
			i++;
		}
	}
	my_tmp[n] = NULL;
	i = 0;
	while (mini->my_export[i]) 
	{
		free(mini->my_export[i]);
		i++;
	}
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