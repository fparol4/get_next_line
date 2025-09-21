/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparola <fparola@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:33:56 by fparola           #+#    #+#             */
/*   Updated: 2025/09/13 14:33:56 by fparola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fn_concat(char *buffer, char *chunk)
{
	int		i;
	int		size_buffer;
	int		size_chunk;
	int		size_concat;
	char	*concated;

	size_buffer = fn_strlen(buffer);
	size_chunk = fn_strlen(chunk);
	if (size_buffer == 0 && size_chunk == 0)
		return (fn_secfree((char **[]){&buffer, &chunk}, 2));
	if (size_chunk == 0)
	{
		fn_secfree((char **[]){&chunk}, 1);
		return (buffer);
	}
	size_concat = size_buffer + size_chunk;
	concated = fn_calloc(size_concat + 1, sizeof(char));
	i = 0;
	while (i++ < size_buffer)
		concated[i - 1] = buffer[i - 1];
	i = 0;
	while (i++ < size_chunk)
		concated[i + size_buffer - 1] = chunk[i - 1];
	fn_secfree((char **[]){&buffer, &chunk}, 2);
	return (concated);
}

char	*fn_cropline(char *buffer)
{
	int		i;
	int		idx;
	char	*line;

	if (buffer == NULL)
		return (NULL);
	idx = fn_cropidx(buffer);
	if (buffer[idx] == '\n')
		++idx;
	line = fn_calloc(idx + 1, sizeof(char));
	i = 0;
	while (i++ < idx)
		line[i - 1] = buffer[i - 1];
	return (line);
}

char	*fn_remain(char *buffer)
{
	int		i;
	int		idx;
	int		size_buffer;
	int		size_remaining;
	char	*remain;

	if (buffer == NULL)
		return (NULL);
	idx = fn_cropidx(buffer);
	if (buffer[idx] == '\n')
		++idx;
	size_buffer = fn_strlen(buffer);
	size_remaining = size_buffer - idx;
	if (size_remaining == 0)
		return (fn_secfree((char **[]){&buffer}, 1));
	remain = fn_calloc(size_remaining + 1, sizeof(char));
	i = 0;
	while (i++ < size_remaining)
		remain[i - 1] = buffer[i + idx - 1];
	fn_secfree((char **[]){&buffer}, 1);
	return (remain);
}

char	*get_next_line(int fd)
{
	int			readed;
	char		*chunk;
	char		*line;
	static char	*buffer;

	if (fd < 0)
		return (NULL);
	chunk = fn_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (chunk == NULL)
		return (fn_secfree((char **[]){&buffer}, 1));
	readed = read(fd, chunk, BUFFER_SIZE);
	if (readed == -1)
		return (fn_secfree((char **[]){&buffer, &chunk}, 2));
	buffer = fn_concat(buffer, chunk);
	if (readed == 0 || fn_isline(buffer))
	{
		line = fn_cropline(buffer);
		buffer = fn_remain(buffer);
		return (line);
	}
	return (get_next_line(fd));
}
