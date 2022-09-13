/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:09:12 by tgarriss          #+#    #+#             */
/*   Updated: 2022/09/11 18:54:47 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>

# define READ_END 0
# define WRITE_END 1

/*--- global variable for "g_envp" ---*/
char							**g_envp;

/*--- Structures ---*/
typedef struct s_commandtable	t_commandtable;
// mode == outfile append or trunc. 1=APPEND, 0=TRUNC
typedef struct s_command
{
	t_commandtable	*table;
	char			*command;
	char			*outfile_path;
	int				mode;
	char			*binary;
	char			**arguments;
	int				num_args;
	int				input;
	int				output;
	int				pipe[2];
	int				has_redir;
}					t_command;

typedef struct s_commandtable
{
	t_command		*commands;
	int				pipe_fd[2];
	int				num_commands;
	t_iarray		*open_files;
	pid_t			pid;
}					t_commandtable;

/*--- utils.c ---*/
int				*f_exit_code(void);
void			wait_child(pid_t pid);
char			*ft_shlvl_strjoin(char const *s1, char const *s2);
char			*ft_level(void);
void			*ft_shlvl(void);

/*--- heredoc.c ---*/
void			heredoc(int fd, char *delim);
char			*fix_line(char *line);
char			*strip_quotes(char *token);

/*--- assignation_utils.c ---*/
int				is_var(char c);
int				check_pipe_valid(char **tokens);
void			add_cmd_to_args(t_commandtable *table);
void			init_command(t_command *command);

/*--- tokenizer.c ---*/
char			*find_token(char *line, int *i);
char			**tokenize(char *line);

/*--- tokens.c ---*/
char			*get_alpha_token(char *line, char *token, int *i);
char			*get_delimiter_token(char *line, int *i);
char			*get_variable_token(char *line, int *i);
char			*get_quotes_token(char *line, char *token, int *i);
char			*get_token(char *line, char *token, int *i);

/*--- expansion ---*/
char			*expand(char *token, char **envp, int remove);

/*--- environment_variables.c ---*/
char			*get_environment_variable(char *token, int *i, char **envp);
char			*add_to_string(char *string, char c);

/*--- lexer.c ---*/
t_commandtable	*parse(char *line);
int				get_num_commands(char **tokens);
void			free_commandtable(t_commandtable *table);

/*--- assignation.c ---*/
t_commandtable	*set_commandtable(char **tokens);
void			set_token(t_command *command, char *token, int index, \
														char **tokens);
void			print_command_table(t_commandtable *table);

/*--- redirection.c ---*/
int				set_redirection(char **tokens, t_commandtable *table, \
															int index);

/*--- builtin_util.c ---*/
char			*ft_cd_strdup(const char *s1);
int				print_and_return(char *str);
int				print_and_return2(void);
int				print_and_return3(char *str);

/*--- exit_util.c ---*/
int				bigger_than_llong(const char *str);

/*--- copy_env.c ---*/
void			ft_env_free(char **s);
char			**ft_copy_env(char **s);
size_t			ft_cnt_ary(char **s);

/*--- export_util.c ---*/
int				ft_export_strcmp(const char *s1, const char *s2);
void			ft_swap(char **env);
void			ft_export_quotes(char *env);
void			print_export(char **env);
char			**ft_export_add(char **s, char *add);

/*--- export_util2.c ---*/
char			*ft_export_check(char *line);
int				ft_export_val_exist(char *line);
void			ft_export_val_change(char *line);
void			ft_export_args(char *line);
int				ft_export_valid(char *line);

/*--- env.c ---*/
int				env_exe(t_command *command);
/*--- echo.c ---*/
int				echo_exe(t_command *command);
/*--- exit.c ---*/
int				exit_exe(t_command *command);
/*--- export.c ---*/
int				export_exe(t_command *command);
/*--- unset.c ---*/
int				unset_exe(t_command *command);
/*--- cd.c ---*/
int				cd_exe(t_command *command);
/*--- pwd.c ---*/
int				pwd_exe(char *line);

/*--- run_builtin.c ---*/
int				run_builtin(t_command *command);
int				run_builtin2(t_command *command);
int				builtin_check(char *cmd);

/*--- bin_util.c ---*/
char			**bin_split(char const *s, char c);

/*--- run_from_bin.c ---*/
void			bin_exe(t_command *command, char **g_envp);

/*--- execute.c ---*/
void			execution(t_commandtable *table);
int				run_builtin(t_command *command);
int				run_from_bin(t_command *command);

/*--- readline.c ---*/
void			setting_signal(void);
void			sig_handler_child(int signal);
void			sig_handler_heredoc(int signal);
void			sig_handler_minishell_recur(void);

/*--- main.c ---*/
void			control_d(t_commandtable *table);

#endif
