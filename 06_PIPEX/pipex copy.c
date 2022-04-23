// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pipex.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
// /*   Updated: 2022/04/22 16:48:27 by minkim           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "pipex.h"

// typedef struct s_god
// {
//     char **envp;
// }   t_god;

// int parse_cmd(t_god *god, char **argv, char **envp)
// {
//     char	*temp_path;

//     god->infile = ft_strdup(argv[1]);
//     god->ps[0].cmd = ft_split(argv[2], ' ');
//     check_slash(&god->ps[0], argv[2]);
//     god->ps[1].cmd = ft_split(argv[3], ' ');
//     check_slash(&god->ps[1], argv[3]);
//     god->outfile = ft_strdup(argv[4]);
//     temp_path = find_path(envp);
//     if (temp_path == NULL && (god->ps[0].slash == FALSE || god->ps[1].slash == FALSE))
//         return (exit_err("wrong path!\n"));
//     god->path = ft_split(temp_path, ':');
//     free(temp_path);
//     return (SUCCESS);
// }

// void check_slash(t_ps *ps, const char *temp)
// {
//     if (ft_strncmp(temp, "/", 1) == 0
//         || ft_strncmp(temp, "./", 2) == 0 || ft_strncmp(temp, "../", 3) == 0)
//         ps->slash = TRUE;
// }

// static char *find_path(char **envp)
// {
//     int		i;
//     char	*ret_path;

//     i = 0;
//     while (envp[i] != NULL)
//     {
//         if (ft_strncmp("PATH=", envp[i], 5) == 0)
//         {
//             ret_path = ft_strdup(envp[i] + 5);
//             return (ret_path);
//         }
//         i++;
//     }
//     return (NULL);
// }

// int check_parse(t_god *god)
// {
//     god->infile_fd = open(god->infile, O_RDWR);
//     if (god->infile_fd < 0)
//         return (exit_perror("not valid infile!"));
//     god->outfile_fd = open(god->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
//     if (god->outfile_fd < 0)
//         return (exit_perror("not valid outfile!"));
//     check_commands(god);
//     return (SUCCESS);
// }

// void check_commands(t_god *god)
// {
//     int i;

//     i = 0;
//     while (i < 2)
//     {
//         if (god->ps[i].slash == FALSE)
//         {
//             if (set_cmd(god, &god->ps[i]) == ERROR)
//                 exit_err("command not found!\n");
//         }
//         else
//             god->ps[i].path = ft_strdup(god->ps[i].cmd[0]);
//         i++;
//     }
// }

// int set_cmd(t_god *god, t_ps *ps)
// {
//     int	i;
//     char *temp_path;
//     char *temp_cpath;

//     i = 0;
//     while (god->path[i])
//     {
//         temp_path = ft_strjoin(god->path[i], "/");
//         temp_cpath = ft_strjoin(temp_path, ps->cmd[0]);
//         if (access(temp_cpath, F_OK) == 0)
//         {
//             ps->path = ft_strdup(temp_cpath);
//             free(temp_path);
//             free(temp_cpath);
//             return (SUCCESS);
//         }
//         free(temp_path);
//         free(temp_cpath);
//         i++;
//     }
//     return (ERROR);
// }


// int main(int argc, char **argv, char **envp)
// {
//     t_god god;

//     if (argc == 5)
//     {
//         ft_memset(&god, 0, sizeof(t_god));
//         god.envp = envp;
//         /* To Do List*/
//         // 1. 파싱함수
//         // 2. 파싱체크
//         // 3. pipex 주요기능 작동함수(pipex_master)
//     }
//     else
//         return (exit_err("wrong command count!"));
//     return (0);
// }