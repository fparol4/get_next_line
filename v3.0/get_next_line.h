/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparola <fabricio.parola@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:59:19 by fparola           #+#    #+#             */
/*   Updated: 2025/09/10 17:59:19 by fparola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#define FILE_NAME "text.txt"
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 16
#endif

#include <stdio.h>
/* libs */
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/* functions */
int f_strlen(char *str);
char *f_search(char *buffer, char c);
void *f_calloc(size_t count, size_t size);
char *f_concat(char *buffer, char *chunk);
char *f_strlcpy(char *buffer, char *chunk, size_t size);
size_t f_cropidx(char *buffer);
char *f_mvcursor(char *buffer, int idx);
char *f_extract(char *buffer, int idx);
char *get_next_line(int fd);

#endif
