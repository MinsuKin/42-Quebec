/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:05:07 by tgarriss          #+#    #+#             */
/*   Updated: 2022/03/27 14:05:21 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_strchr(char *src, int c);
char	*gnl_cropsave(char *src);
char	*gnl_cropline(char *src);
size_t	gnl_strlen(char *string);

#endif
