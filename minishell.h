/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:37:48 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/18 19:47:37 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "./utils/ft_libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

typedef struct s_prep
{
	int		i;
	int		j;
	int		eof_counter;
	int		fl;
	int		tab;
	char	*str;
	char	*var;
	int		fd[2];
	size_t	nb;
	int		*pid;
}	t_prep;

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
	int		files_nb;
	int		std_in;
	int		std_out;
	int		exit_code;
}	t_cmd_info;

typedef struct s_cmd
{
	char		*cmd;
	char		**args;
	int			pipe;
	int			fd_in;
	int			fd_out;
	char		**files;
	int			append;
	int			here_doc;
	char		**eof;
	int			out_red;
	int			in_red;
	t_cmd_info	*general_info;
}	t_cmd;

typedef struct s_minishell
{
	char	**tmp_cmd;
	char	**cmd;
	int		cmd_nb;
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
	int		no_exp;
	int		do_not_exp;
	int		deuble;
	int		ambg;
	int		max;
}	t_minishell;

//built_in
void	built_in_cmd(t_minishell	*mini, char **env);
void	built_in_cmd_2(t_minishell	*mini, t_cmd	*cmd, char **env);
int		ft_cd(t_cmd	*cmd, t_minishell	*mini);
void	ft_cd_ext(t_minishell	*mini, int i, int *check);
void	ft_pwd(void);
int		built_in_cmd_3(t_minishell	*mini, t_cmd	*cmd);
int		built_in_cmd_ext(t_minishell	*mini, char	*str);

//exit
void	ft_exit(t_cmd	*cmd, t_minishell	*mini);
void	ft_exit_ext(t_cmd	*cmd);
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
void	ft_rem_var(char	**str, t_minishell	*mini, int t);
void	ft_rem_var_export(char **str, t_minishell *mini, int t);
void	print_export(t_minishell *mini);
int		ft_double_single_quote(char *str);
int		ft_check_var_exect(char *s, t_minishell *mini, int var);

//parce_1
char	*prep(char	*str, t_minishell	*mini);
void	prep_ext_1(t_minishell	*mini, t_prep	*prep, char	*str);
void	prep_ext_2(t_minishell	*mini, t_prep	*prep, char	*str);
void	prep_ext_3(t_minishell	*mini, t_prep	*prep, char	*str);
void	prep_ext_4(t_prep	*prep, char	*str);

//parce_1_ext
void	prep_ext_5(t_prep	*prep, char	*str);
void	prep_ext_6(t_minishell	*mini, t_prep	*prep, char	*str);

//parce_2
void	parcing(t_minishell	*mini, t_cmd	*cmd, char *s);
void	to_struct(t_minishell	*mini, t_cmd	*cmd);
void	to_struct_2(t_cmd	*cmd, t_cmd_info	*general_info, \
t_minishell	*mini);
void	tokenisation_1(t_cmd	*cmd, t_cmd_info	*general_info, \
t_minishell	*mini, t_prep	*prep);
void	tokens_redirection(t_cmd	*cmd, t_cmd_info	*general_info, \
t_prep	*prep);

//parce_2_ext
int		cmd_counter(t_minishell	*mini);
int		*args_counter(t_cmd_info	*general_info);
int		args_counter_ext(t_cmd_info	*general_info, int *i, int *j);
void	init_tokenisation(t_cmd	*cmd, t_cmd_info	*general_info, int tab);
void	init_general_info(t_cmd_info	*general_info, t_minishell	*mini);

//error
int		ft_double_single_quote(char *str);
int		ft_error_pipe(char *s);
int		ft_error(char *str, int i);

//ft_error_2
int		ft_error_2(t_minishell	*mini);
int		first_error_part(t_minishell	*mini, char	*str);
int		pipes_error(t_minishell	*mini, int i);
int		more_pipes_error(t_minishell	*mini, int i);

//ft_error_2_ext
int		check_first_cmd(char	*s);
int		check_first_cmd_d(char	*s);
int		check_first_cmd_s(char	*s);
int		check_first_cmd_ext(char	*s, int i, int check);

//expantion
void	ft_check_dollar1(t_minishell *mini);
void	ft_expand(int n, char *s, t_minishell *mini);
void	handle_single(char *s, int *i, int *j, t_minishell *mini, int *n);
void	handle_double(char *s, int *i, int *j, t_minishell *mini, int *n);
int		expand_var(char *s, char *d, int *j, t_minishell *mini);
int		get_len(char *s, t_minishell *mini, int len);
char	*get_value(char *str, t_minishell *mini);
char	*get_key(char *str);

//expantion heredoc
void	ft_check_dollar_heredoc(t_minishell *mini, char	*var, char	**res);
void	ft_expand_heredoc(int n, char *s, t_minishell *mini, char	**res);

//execution
void	exec_1(t_minishell	*mini, t_cmd	*cmd, char	**env);
int		exec_1_ext(t_cmd	*cmd, t_minishell	*mini, t_prep	*prep, \
char	**env);
int		multi_cmd(t_cmd	*cmd, t_minishell	*mini, t_prep	*prep, char	**env);
int		single_cmd(t_cmd	*cmd, t_minishell	*mini, t_prep	\
*prep, char	**env);

//execution_2
void	execv_function(t_minishell	*mini, t_cmd	*cmd);
void	execve_func_ext(t_minishell	*mini, t_cmd	*cmd);
void	execve_func_ext_1(t_minishell	*mini, t_cmd	*cmd, int \
i, char	**var);
void	execve_error(t_minishell	*mini, t_cmd	*cmd);

//execution_3
int		check_ambig(char	*file, t_minishell	*mini);
int		check_ambig_ext(char	*file, t_minishell	*mini);

//here_doc
void	ft_check_dollar_heredoc(t_minishell *mini, char	*s, char	**res);
int		here_doc(t_cmd	*cmd, t_minishell	*mini);
int		here_doc_ext(t_cmd	*cmd, t_minishell	*mini, t_prep	*prep, \
int	*fd);
void	here_doc_ext_1(char	**res, char	*read, int	*fd);
int		here_doc_ext_2(char	*read, t_cmd	*cmd, t_prep	*prep);

//file_creation
void	redirections(t_cmd	*cmd, t_minishell	*mini);
void	file_creation(t_cmd	*cmd, t_minishell	*mini);
void	append_files(t_cmd	*cmd, int j);
void	out_redirection_files(t_cmd	*cmd, int j);
void	in_redirection_files(t_cmd	*cmd, int j);

//leaks
void	to_free(t_cmd	*cmd);
void	to_free_1(t_minishell	*mini, char	**ret);
void	to_free_ext(char	*var, char	*str, char	*s);

#endif