/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:09:12 by tgarriss          #+#    #+#             */
/*   Updated: 2022/07/19 18:23:41 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>

# define READ_END 0
# define WRITE_END 1

/*--- global variable for "g_envp" ---*/
char			**g_envp;

/*--- Structures ---*/
typedef struct s_commandtable	t_commandtable;
typedef struct s_command
{
	t_commandtable				*table;
	char						*command;
	char						*binary;
	char						**options;
	char						**arguments;
	int							num_args;
	int							num_options;
	int							input;
	int							output;
	int							pipe[2];
}								t_command;

typedef struct s_commandtable
{
	t_command					*commands;
	int							pipe_fd[2];
	int							num_commands;
	t_iarray					*open_files;
}								t_commandtable;

typedef struct s_quotestruct
{
	int							within_quotes;
	char						quote_type;
}								t_quotestruct;

/*--- lexer.c ---*/
t_commandtable	*parse(char *line);
int				get_num_commands(char **tokens);
int				is_symbol(char c);
void			free_commandtable(t_commandtable *table);

/*--- assignation.c ---*/
t_commandtable	*set_commandtable(char **tokens);
void			set_token(t_command *command, char *token, int index, char **tokens);
void			set_commands(t_commandtable *table, char **tokens);
void			print_command_table(t_commandtable *table);


/*--- builtin_util.c ---*/
char			*ft_cd_strdup(const char *s1);
int				print_and_return(char *str);

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
void			ft_export_insert(t_command *command);

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
void			wait_child(void);

/*--- readline.c ---*/
void							setting_signal(void);
void							sig_handler_child(int signal);
void							sig_handler_heredoc(int signal);

/*--- main.c ---*/
void							control_d(t_commandtable *table);
int								*f_exit_code(void);

/*--- redirection.c ---*/
int				set_redirection(char **tokens, t_commandtable *table, int index);

/*--- tokenizer.c ---*/
char			**tokenizer(char *line);
void			ft_print_sarray(char **array);

/*--- expansion.c ---*/
char			*find_environment_variable(char *var, char **g_envp);
char			*add_to_string(char *string, char c);

/*--- assignation.c ---*/
void			init_command(t_command *command);

#endif
