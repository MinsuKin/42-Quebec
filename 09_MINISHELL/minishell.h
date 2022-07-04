/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:09:12 by tgarriss          #+#    #+#             */
/*   Updated: 2022/07/04 14:53:43 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/includes/libft.h"

# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <termios.h>

# define READ_END 0
# define WRITE_END 1

/*--- Structures ---*/
typedef struct s_commandtable t_commandtable;
typedef struct s_command
{
	t_commandtable	*table;
	char			*command;
	char			*binary;
	char			**options;
	char			**arguments;
	int				num_args;
	int				num_options;
	int				input;
	int				output;
}	t_command;

typedef struct s_commandtable
{
	t_command	*commands;
	int			pipe_fd[2];
	int			num_commands;
	t_iarray	*open_files;
}	t_commandtable;

typedef struct s_quotestruct
{
	int		within_quotes;
	char	quote_type;
}	t_quotestruct;

/*--- main.c ---*/
void    control_d(void);

/*--- lexer.c ---*/
t_commandtable	*parse(char *line);
int				get_num_commands(char **tokens);
int				is_symbol(char c);
void			free_commandtable(t_commandtable *table);

/*--- syntax.c ---*/
int				check_syntax_valid(char *line);
int				check_pipe_format_valid(char *line);
int				check_redirection_valid(char *line);
int				find_num_of_quotes(char *line, t_quotestruct q);

/*--- format.c ---*/
char			*add_whitespace(char *line, int new_len);
char			*reformat_string(char *line);
char			*remove_whitespace(char *line, int new_len);
int				find_len_added_whitespace(char *line);
int				find_len_no_whitespace(char *line);

/*--- expansion.c ---*/
char			*expand(char *line, char **envp);
char			*expand_variable(char *line, char **envp, int index);
char			*insert_into_new_string(char *line, char *insert, char *var);
char			*trim_var_from_string(char *line, char *var);
char			*find_environment_variable(char *var, char **envp);

/*--- global variable for "envp" ---*/
char			**envp;

/*--- builtin_util.c ---*/
char			*ft_cd_strdup(const char *s1);
int				print_and_return(char *str);

/*--- exit_util.c ---*/
int				bigger_than_llong(const char *str);

/*--- exit.c ---*/
int				exit_exe(char *line);

/*--- echo.c ---*/
int				echo_exe(char *line);

/*--- copy_env.c ---*/
void			ft_env_free(char **s);
char			**ft_copy_env(char **s);
size_t			ft_cnt_ary(char **s);

/*--- copy_env.c ---*/
int				env_exe(char *line);

/*--- export_util.c ---*/
int				ft_export_strcmp(const char *s1, const char *s2);
void			ft_swap(char **env);
void			ft_export_quotes(char *env);
void			print_export(char **env);
char			**ft_export_add(char **s, char *add);

/*--- tmp global variable for "env" ---*/
char			**envp;

/*--- copy_env.c ---*/
void			ft_env_free(char **s);
char			**ft_copy_env(char **s);

/*--- export.c ---*/
int				export_exe(char *line);

/*--- expansion.c ---*/
char			*expand(char *line, char **envp);
char			*expand_variable(char *line, char **envp, int index);
char			*insert_into_new_string(char *line, char *insert, char *var);
char			*trim_var_from_string(char *line, char *var);
char			*find_environment_variable(char *var, char **envp);
void			check_for_quote(char *c, t_quotestruct *quotes);

/*--- unset.c ---*/
int				unset_exe(char *line);

/*--- cd.c ---*/
int				cd_exe(char *line);

/*--- bin_util.c ---*/
// static char		*ft_strndup(const char *s1, size_t n);
char			**bin_split(char const *s, char c);

/*--- run_from_bin.c ---*/
void			bin_exe(char *argv, char **envp);

/*--- signal(main.c) ---*/
void			setting_signal(void);
void			sig_handler_child(int signal);

/*--- execute.c ---*/
void			execution(char *line);
int				run_builtin(char *line);
int				run_from_bin(char *line);

/*--- tokenization.c ---*/
char			**tokenize(char *l);
char			**add_to_array(char **array, char *insert);

/*--- assignation.c ---*/
t_commandtable	*set_commandtable(char **tokens);
void			set_token(t_command *command, char *token, int index, char **tokens);
void			set_commands(t_commandtable *table, char **tokens);
void			print_command_table(t_commandtable *table);

#endif
