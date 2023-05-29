/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:37:48 by aachfenn          #+#    #+#             */
/*   Updated: 2023/05/29 20:41:24 by aachfenn         ###   ########.fr       */
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

typedef struct s_cmd_info
{
	char	**str;
	int		cmd_nb;
	int		pipe_nb;
	int		append_nb;
	int		out_red_nb;
	int		in_red_nb;
	int		here_doc_nb;
}	t_cmd_info;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	int		pipe;

	//file descriptors
	int	fd_in;
	int	fd_out;
	
	//
	int		append;
	char	*append_file;
	//
	int		here_doc;
	char	**eof;
	//
	int		out_red;
	char	*out_red_file;
	//
	int		in_red;
	char	*in_red_file;
	
	t_cmd_info	*general_info;
}	t_cmd;

typedef struct s_minishell
{
	char	**tmp_cmd;
	char	**cmd;
	int		cmd_nb;
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
void	built_in_cmd_2(t_minishell	*mini, t_cmd	*cmd, char **env);
void	execv_function(t_minishell	*mini, t_cmd	*cmd, char **env);
int		ft_cd(t_cmd	*cmd);
void	ft_pwd();

//command
void	ft_echo(t_cmd	*cmd);
void	ft_env(char **env, t_minishell *mini);
int		ft_cnt(char *str);
char	**ft_env_1(char **env, t_minishell *mini);
void	ft_tmp_my_env(t_minishell *mini);
void	ft_add_declare(t_minishell *mini);

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
int		ft_double_single_quote(char *str);
int		ft_check_var_exect(char *s,t_minishell *mini, int var);


//parcing
void	parcing(t_minishell	*mini,t_cmd	*cmd, char *s);
char	*prep(char *str);


//parce_2
void	to_struct(t_minishell	*mini, t_cmd	*cmd);
void	to_struct_2(t_cmd	*cmd, t_cmd_info	*general_info);
int		cmd_counter(t_minishell	*mini);

//error
int		ft_double_single_quote(char *str);
int		ft_error_pipe(char *s);
int		ft_error(char *str);

//expantion
void	ft_check_dollar(t_minishell *mini);

//execution
void	exec_1(t_minishell	*mini, t_cmd	*cmd, char	**env);


int	*args_counter(t_cmd_info	*general_info);

#endif