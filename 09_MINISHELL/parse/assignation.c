/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:01:33 by tgarriss          #+#    #+#             */
/*   Updated: 2022/07/04 12:42:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "time.h"

char	**add_to_unclosed_pipe(char **tokens)
{
	char	**add_tokens;
	char	*new_line;
	char	*line;
	int		i;

	i = -1;
	add_tokens = NULL;
	line = NULL;
	while (tokens[++i])
	{
		if (tokens[i][0] == '|' && !tokens[i + 1])
		{
			line = readline("pipe> ");
			if (!line)
				control_d();
			else if (*line == '\0')
				free(line);
			else
			{
				new_line = reformat_string(line);
				add_tokens = tokenize(new_line);
				free(new_line);
			}
		}
		else if (tokens[i][0] == '|' && (tokens[i + 1][0] == '|' || tokens[i][1] == '|'))
		{
			// change this
			ft_error("unexpected parse error near |", __FILE__, __func__, __LINE__);
		}
	}
	if (!add_tokens)
		return (tokens);
	i = -1;
	while (add_tokens[++i])
		tokens = add_to_array(tokens, add_tokens[i]);
	free(add_tokens);
	return (tokens);
}

int	unclosed_pipe_loop(char **tokens)
{
	int	i;

	if (!tokens)
		return (0);
	i = 0;
	while (tokens[i])
		i++;
	if (tokens[i - 1][0] == '|')
		return (1);
	return (0);
}

void	write_to_fd(int fd[2], char *delim)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (ft_strcmp(line, delim) != 0)
	{
		ft_putstr_fd(line, fd[WRITE_END]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
}

// here, gotta gnl user input from stdin until delim
// then set stdin->fd[0] for next iter
void	here_doc(char *delim)
{
	int		fd[2];
	int		pid;

	// fix this so it exits properly.
	if (pipe(fd) == -1)
		ft_error("pipe() failed.", __FILE__, __func__, __LINE__);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		write_to_fd(fd, delim);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int	set_redirection(char **tokens, t_commandtable *table, int index)
{
	if (!tokens)
		return (0);
	if (!tokens[1] || tokens[1][0] == '|')
		return (0);
	if (ft_strlen(*tokens) == 2)
	{
		if (**tokens == '>')
		{
			table->commands[index].output = open(tokens[1], O_CREAT | O_APPEND, 0777);
			table->open_files = ft_add_to_iarray(table->open_files, table->commands[index].output);
		}
		else if (**tokens == '<')
		{
			here_doc(tokens[1]);
			// fix this so it exits properly.
			if (!tokens[1] || tokens[1][0] == '|')
				return (0);
			// add in/out assignation
		}
	}
	else if (ft_strlen(*tokens) == 1)
	{
		if (**tokens == '>')
		{
			table->commands[index].output = open(tokens[1], O_RDWR | O_CREAT, 0777);
			table->open_files = ft_add_to_iarray(table->open_files, table->commands[index].output);
		}
		else if (**tokens == '<')
		{
			table->commands[index].input = open(tokens[1], O_RDWR | O_CREAT, 0777);
			table->open_files = ft_add_to_iarray(table->open_files, table->commands[index].input);
		}
	}
	if (table->commands[index].input == -1 || table->commands[index].output == -1)
		return (0);
	return (1);
}

// Need to have char **envp expansion to work... Could we store it in the commandtable?
extern char **environ;
int	assign_token(char **tokens, t_commandtable *table, int index)
{
	char	*new_token;

	new_token = expand(*tokens, environ);
	if (table->commands[index].command == NULL)
		table->commands[index].command = ft_strdup(new_token);
	else
	{
		table->commands[index].arguments = add_to_array(table->commands[index].arguments, ft_strdup(new_token));
		table->commands[index].num_args = ft_get_array_length(table->commands[index].arguments);
	}
	free(new_token);
	return (1);
}

// I'm getting leaks with: "echo -n 10 stuff < infile |stuff arguments >outfile | foobla"
// it seems to be coming from my add_to_array function.
int	set_tokens(char **tokens, t_commandtable *table)
{
	int	i;
	int	j;

	if (!tokens || ! table)
		return (0);
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|')
			j++;
		else if (tokens[i][0] == '>' || tokens[i][0] == '<')
		{
			if (set_redirection(&tokens[i], table, j))
				i++;
		}
		else
		{
			assign_token(&tokens[i], table, j);
		}
		i++;
	}
	return (1);
}

void	set_pipes(t_commandtable *table)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	// fix this so it exits properly.
	if (pipe(table->pipe_fd) == -1)
		ft_error("pipe() failed.", __FILE__, __func__, __LINE__);
	while (i < table->num_commands)
	{
		table->commands[i].table = table;
		table->commands[i].input = STDIN_FILENO;
		table->commands[i].output = STDOUT_FILENO;
		i++;
	}
	i = 0;
	while (i < table->num_commands)
	{
		if (i == 0 && table->num_commands > 1)
		{
			table->commands[i].input = STDIN_FILENO;
			table->commands[i].output = table->pipe_fd[WRITE_END];
		}
		else if (i == 0 && table->num_commands == 1)
		{
			table->commands[i].input = STDIN_FILENO;
			table->commands[i].output = STDOUT_FILENO;
		}
		else if (i > 0 && i < table->num_commands - 1)
		{
			table->commands[i].input = table->pipe_fd[READ_END];
			table->commands[i].output = table->pipe_fd[WRITE_END];
		}
		else
		{
			table->commands[i].input = table->pipe_fd[READ_END];
			table->commands[i].output = STDOUT_FILENO;
		}
		i++;
	}
}

void	print_command_table(t_commandtable *table)
{
	int	i;
	int	j;

	if (!table)
		return ;
	i = 0;
	printf("pipeIN: %d, pipeOUT: %d\n", table->pipe_fd[READ_END], table->pipe_fd[WRITE_END]);
	while (i < table->num_commands)
	{
		printf("--- %d ---\n", i);
		printf("Command: %s\n", table->commands[i].command);
		j = 0;
		printf("Args: ");
		while (j < table->commands[i].num_args)
		{
			printf("%s, ", table->commands[i].arguments[j]);
			j++;
		}
		printf("\n");
		printf("Input: %d Output: %d\n", table->commands[i].input, table->commands[i].output);
		i++;
	}
	if (table->open_files)
	{
		i = 0;
		printf("open files: ");
		while (i < table->open_files->size)
		{
			printf("%d, ", table->open_files->array[i]);
			i++;
		}
		printf("\n");
	}
}

// here_docs are not implemented yet. Need to figure out how that works first.
t_commandtable	*set_commandtable(char **tokens)
{
	t_commandtable	*table;

	if (!tokens)
		return (NULL);
	table = ft_calloc(1, sizeof(t_commandtable));
	if (!table)
		ft_error("Table creation failed.", __FILE__, __func__, __LINE__);
	while (unclosed_pipe_loop(tokens))
		tokens = add_to_unclosed_pipe(tokens);
	table->num_commands = get_num_commands(tokens);
	table->commands = ft_calloc(table->num_commands, sizeof(t_command));
	table->open_files = NULL;
	set_pipes(table);
	// fix this so it exits properly.
	if (!set_tokens(tokens, table))
		ft_error("token assignation failed.", __FILE__, __func__, __LINE__);
	return (table);
}

// int	main(void)
// {
// 	// t_commandtable	*table;
// 	char			**array;
// 	char			*string;

// 	// string = ft_strdup("echo stuff <<\"<infile >outfile| grep << bla>>outfile| ");
// 	//string = ft_strdup("ls $ARG > out << EOF | grep 'foobla' <infile |wc -l");
// 	string = ft_strdup("echo $ARG | < outfile cat | grep stuff > infile");
// 	array = tokenize(string);
// 	// table = parse(string);
// 	// free_commandtable(table);
// 	ft_free_carray(array);
// 	free(string);
// }