/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:37:48 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/19 21:46:25 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
#define	MINISHELL_H
 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "./utils/ft_libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_minishell
{
	char	*home;
	char	*variable;
	char	**str;
	int		count_str;
	char	**my_env;
	char	**my_export;
	char	**tmp_my_env;
}	t_minishell;

void	ft_echo(t_minishell *mini);

void	built_in_cmd(t_minishell	*mini, char **env);
int		ft_cd(t_minishell	*mini);
void	ft_pwd();
void	ft_env(char **env, t_minishell *mini);
void	ft_export(t_minishell *mini);
void	ft_rem_var(char **str, t_minishell *mini);
char	**ft_env_1(char **env, t_minishell *mini);
void	ft_add_declare(t_minishell *mini);

#endif