/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:37:48 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/21 15:04:07 by aachfenn         ###   ########.fr       */
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
#include <fcntl.h>

typedef struct s_minishell
{
	char	*var;

	//built_in
	char	*home;
	char	*variable;
	char	**str;
	int		count_str;
	char	**my_env;
	char	**my_export;
	char	**tmp_my_env;
}	t_minishell;

//built_in
void	built_in_cmd(t_minishell	*mini, char **env);
void	built_in_cmd_2(t_minishell	*mini, char **env);
void	execv_function(t_minishell	*mini, char **env);
int		ft_cd(t_minishell	*mini);
void	ft_pwd();

//command
void	ft_echo(t_minishell *mini);
void	ft_env(char **env, t_minishell *mini);
int		ft_cnt(char *str);
char	**ft_env_1(char **env, t_minishell *mini);
void	ft_tmp_my_env(t_minishell *mini);
void	ft_add_declare(t_minishell *mini);
void	ft_add_declare_in_pos(t_minishell *mini);

//ft_unset
void	ft_unset(t_minishell *mini);
void	search_in_env(t_minishell	*mini, char *str);
void	rem_var_env(t_minishell	*mini, int pos);
void	search_in_export(t_minishell	*mini, char *str);
void	rem_var_export(t_minishell	*mini, int pos);

//ft_export
void	ft_export(t_minishell *mini);
void	ft_rem_var(char **str, t_minishell *mini);
void	ft_rem_var_export(char **str, t_minishell *mini);
void	print_export(t_minishell *mini);

//parcing
void	parcing(t_minishell	*mini, char *s);
void	prep(char *str);
char	*unwanted_spaces(char	*str);
void	return_umprint_to_space(char	*var);
void	space_to_imprint_dcotes(char	*str);
void	space_to_imprint_scotes(char	*str);


#endif