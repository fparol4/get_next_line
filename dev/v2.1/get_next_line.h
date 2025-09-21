/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparola <fparola@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:46:13 by fparola           #+#    #+#             */
/*   Updated: 2025/09/06 19:46:13 by fparola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# include <stdio.h>

# define GET_NEXT_LINE_H
# define FILE_NAME "text.txt"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 17
# endif

// required-libs
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

// utils
void	panic(char *s);
int		f_strlen(const char *str);
char	*f_search(char *s, char c);
char	*f_concat(char *original, char *chunk);
size_t	f_strlcpy(char *dst, const char *src, size_t n);
char	*get_next_line(int fd);

#endif
