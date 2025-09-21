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

int	f_strlen(const char *str)
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
	char	*buffer_u;

	size_b = f_strlen(buffer);
	size_c = f_strlen(chunk);
	if (size_b == 0 && size_c == 0)
	{
		free(buffer);
		free(chunk);
		return (NULL);
	}
	buffer_u = malloc((size_b + size_c + 1) * sizeof(char));
	if (buffer_u == NULL)
		return (NULL);
	i = 0;
	while (i < size_b)
	{
		buffer_u[i] = buffer[i];
		i++;
	}
	i = 0;
	while (i < size_c)
	{
		buffer_u[i + size_b] = chunk[i];
		i++;
	}
	buffer_u[i + size_b] = '\0';
	free(buffer);
	free(chunk);
	return (buffer_u);
}

size_t	f_strlcpy(char *dst, const char *src, size_t n)
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
