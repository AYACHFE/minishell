/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:37:48 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/12 11:10:05 by aachfenn         ###   ########.fr       */
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
	int		in_file_exist;
	char	**str;
	int		cmd_nb;
	int		pipe_nb;
	int		append_nb;
	int		out_red_nb;
	int		in_red_nb;
	int		here_doc_nb;
	char	**files;
	char	**eof;
	int		files_nb;
	int		std_in;
	int		std_out;
	int		exit_code;
}	t_cmd_info;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	int		pipe;

	//file descriptors
	int	fd_in;
	int	fd_out;
	
	char	**files;
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
	int		exit_code;

	int		left_sp;
	int		right_sp;
	int		center_sp;
	int		just_sp;
}	t_minishell;

t_cmd *cmd; 
// t_minishell	mini;

//built_in
void	built_in_cmd(t_minishell	*mini, char **env);
void	built_in_cmd_2(t_minishell	*mini, t_cmd	*cmd, char **env);
void	execv_function(t_minishell	*mini, t_cmd	*cmd, char **env);
int		ft_cd(t_cmd	*cmd, t_minishell	*mini);
void	ft_pwd();
int		built_in_cmd_3(t_minishell	*mini, t_cmd	*cmd, char **env);
int		built_in_cmd_3_check(t_minishell	*mini, t_cmd	*cmd, char **env);

//tmp
void	split_after_expantion(t_minishell	*mini);

//exit
void	ft_exit(t_cmd	*cmd, t_minishell	*mini);
int		ft_toint_check(char *str);
int		ft_toint_check_ext(char *str, int i, int res);

//command
void	ft_echo(t_cmd	*cmd);
void	ft_env(char **env, t_minishell *mini);
int		ft_cnt(char *str);
char	**ft_env_1(char **env, t_minishell *mini);
void	ft_tmp_my_env(t_minishell *mini);
void	ft_add_declare(t_minishell *mini);

//ft_unset
void	ft_unset(t_cmd	*cmd, t_minishell	*mini);
void	search_in_env(t_minishell	*mini, char *str);
void	rem_var_env(t_minishell	*mini, int pos);
void	search_in_export(t_minishell	*mini, char *str);
void	rem_var_export(t_minishell	*mini, int pos);

//ft_export
void	ft_export(t_cmd	*cmd, t_minishell *mini);
void    ft_rem_var(char **str, t_minishell *mini, int t);
void	ft_rem_var_export(char **str, t_minishell *mini, int t);
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
int		*args_counter(t_cmd_info	*general_info);

//error
int		ft_double_single_quote(char *str);
int		ft_error_pipe(char *s);
int		ft_error(char *str, int i);

//ft_error_2
int		ft_error_2(t_minishell	*mini);
int		check_first_cmd(char	*s);
int		check_first_cmd_d(char	*s);
int		check_first_cmd_s(char	*s);
int		first_error_part(t_minishell	*mini, char	*str);

//expanding
void	ft_check_dollar(t_minishell *mini);
char	*ft_change_var(char *str, t_minishell *mini, int tmp);
int		ft_strlenn(char *str);
int		ft_strlennn(char *str);
void	ft_check_sp(char *s, t_minishell *mini);
char	*ft_substr1(char const *s, unsigned int start, size_t len);
int		ft_hsb(char *s);
int		ft_hsb3(char *str, int n);


//execution
void	exec_1(t_minishell	*mini, t_cmd	*cmd, char	**env);
void	file_creation(t_cmd	*cmd, t_minishell	*mini);
void	here_doc(t_cmd	*cmd, t_minishell	*mini);
void	redirections(t_cmd	*cmd, t_minishell	*mini);
void    ft_check_dollar_heredoc(t_minishell *mini, char	*s, char	**res);

#endif