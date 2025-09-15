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
#include <fcntl.h>

void	*fn_clean(char *buffers[], size_t size)
{
	size_t	i;	

	i = 0;
	while (i++ < size)
		if (buffers[i - 1] != NULL)
			free(buffers[i - 1]);
	return (NULL);
}

char	*fn_concat(char *buffer, char *chunk)
{
	size_t	i;
	size_t	s_chunk;
	size_t	s_buffer;
	size_t	s_concated;
	char	*b_concated;

	s_chunk = fn_strlen(chunk); 
	s_buffer = fn_strlen(buffer);
	if (s_chunk == 0)
	{
		fn_clean((char*[]){ chunk }, 1);
		return (buffer);
	}
	s_concated = s_buffer + s_chunk;
	b_concated = fn_calloc(s_concated + 1, sizeof(char));
	if (b_concated == NULL)
		return fn_clean((char*[]){ buffer, chunk }, 2);
	i = 0;
	while (i++ < s_buffer)
		b_concated[i - 1] = buffer[i - 1];
	i = 0;
	while (i++ < s_chunk)
		b_concated[i + s_buffer - 1] = chunk[i - 1];
	b_concated[i  + s_buffer - 1] = '\0';
	fn_clean((char*[]){ buffer, chunk }, 2);
	return (b_concated);
}

char	*fn_crop(char *buffer, size_t idx)
{
	size_t	i;
	size_t	b_size;
	char	*b_crop;

	if (buffer == NULL)
		return (NULL);

	b_size = idx;
	if (buffer[idx] == '\n')
		b_size += 1;
	b_crop = fn_calloc(b_size + 1, 1);
	i = 0;
	while (i++ < b_size)
		b_crop[i - 1] = buffer[i - 1];
	b_crop[i - 1] = '\0';
	return (b_crop);
}

char	*fn_movecursor(char	*buffer, size_t idx)
{
	size_t		i;
	size_t		s_buffer;
	size_t		s_remaining;
	char		*b_remaining;

	if (buffer == NULL)
		return (NULL);
	
	s_buffer = fn_strlen(buffer);
	if (s_buffer == idx)
		return fn_clean((char*[]){ buffer }, 1);

	s_remaining = fn_strlen(buffer + idx + 1);
	if (s_remaining == 0)
		return fn_clean((char*[]){ buffer }, 1);

	b_remaining = fn_calloc(s_remaining + 1, 1);
	if (b_remaining == NULL)
		return fn_clean((char*[]){ buffer }, 1);

	i = 0;
	while (i++ < s_remaining)
		b_remaining[i - 1] = buffer[i + idx]; 
	b_remaining[i - 1] = '\0';

	fn_clean((char*[]){ buffer }, 1);
	return (b_remaining);
}

char	*get_next_line(int fd)
{
	int			readed;
	int		cropidx;
	char		*line;
	char		*chunk;
	static char *buffer;

	if (fd == 0)
		return (NULL);
	
	chunk = fn_calloc(BUFFER_SIZE + 1, 1);
	if (chunk == NULL)
		return (fn_clean((char*[]){ buffer, chunk }, 2));

	readed = read(fd, chunk, BUFFER_SIZE);
	if (readed == -1)
		return (fn_clean((char*[]){ buffer, chunk }, 2));
	chunk[readed] = '\0';

	buffer = fn_concat(buffer, chunk);

	if (readed == 0 || fn_isline(buffer))
	{
		cropidx = fn_cropidx(buffer);
		if (cropidx == -1)
			return (fn_clean((char*[]){ buffer }, 1));
		line = fn_crop(buffer, cropidx);	
		buffer = fn_movecursor(buffer, cropidx);
		return (line);
	}
	return (get_next_line(fd));
}

// int	__T_01__() {
// 	int fd	= open("text.txt", O_RDONLY);
// 	for (int i = 1; i <= 12; ++i) {
// 		char *l = get_next_line(fd);
// 		printf("L: %s$\n", l);
// 		free(l);
// 	}
// 	close(fd);
// }
//
// int	main()
// {
// 	__T_01__();
// 	// char *b = fn_string("orange", -1);
// 	// char *d = fn_string("apple", -1);
// 	// char *r = fn_concat(b, d);
// 	// printf("R: %s$\n", r);
// 	// fn_clean((char*[]){ r }, 1);
//
// }
