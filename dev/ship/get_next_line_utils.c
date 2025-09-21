/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparola <fparola@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:46:23 by fparola           #+#    #+#             */
/*   Updated: 2025/09/06 19:46:23 by fparola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	f_strlen(char *str)
{
	int	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*f_search(char *s, char c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

char	*f_concat(char *buffer, char *chunk)
{
	int		i;
	int		size_b;
	int		size_c;
	char	*buffer_c;

	size_b = f_strlen(buffer);
	size_c = f_strlen(chunk);
	if (size_b == 0 && size_c == 0)
	{
		free(chunk);
		free(buffer);
		return (NULL);
	}
	buffer_c = calloc((size_b + size_c + 2), sizeof(char));
	if (buffer_c == NULL)
		return (NULL);
	i = 0;
	while (i++ < size_b)
		buffer_c[i - 1] = buffer[i - 1];
	i = 0;
	while (i++ < size_c)
		buffer_c[i - 1 + size_b] = chunk[i - 1];
	buffer_c[i + size_b] = '\0';
	free(buffer);
	free(chunk);
	return (buffer_c);
}

size_t	f_strlcpy(char *dst, char *src, size_t n)
{
	size_t	i;
	size_t	s_len;

	s_len = f_strlen(src);
	if (n == 0)
		return (s_len);
	i = 0;
	while (i < n - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (s_len);
}
