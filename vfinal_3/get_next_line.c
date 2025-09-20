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
#include <stdlib.h>
#include <sys/types.h>

void	*fn_secfree(char **buffer)
{
	if (*buffer != NULL)
		free(buffer);
	*buffer = NULL;
	return buffer;
}

char	*fn_concat(char *buffer, char *chunk)
{
	int s_buffer = fn_strlen(buffer);
	int s_chunk = fn_strlen(chunk); 
	int s_concated = s_chunk + s_buffer;

	char *b_concated = fn_calloc(s_concated + 1, sizeof(char));
	if (b_concated == NULL)
		return (NULL);

	int i = 0;
	while (i++ < s_buffer)
		b_concated[i - 1] = buffer[i - 1];

	i = 0;
	while (i++ < s_chunk)
		b_concated[i + s_buffer - 1] = chunk[i - 1];

	b_concated[i  + s_buffer - 1] = '\0';
	return (b_concated);
}

char	*fn_crop(char *buffer)
{
	
}

char	*fn_remain(char *buffer)
{

}


char	*get_next_line(int fd)
{
	int			readed;
	char		*chunk;
	char		*concated = NULL;
	static char *buffer;


	if (fd == 0)
		return (NULL);

	chunk = fn_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (chunk == NULL) {
		fn_secfree(&buffer);
		return (NULL);
	}

	readed = read(fd, chunk, BUFFER_SIZE);
	if (readed == -1) {
		fn_secfree(&buffer);
		fn_secfree(&chunk);
		return (NULL);
	}
	chunk[readed] = '\0';

	if (readed > 0)
		 concated = fn_concat(buffer, chunk);

	fn_secfree(&buffer);
	fn_secfree(&chunk);
	buffer = concated;

	if (buffer == NULL)
		return (NULL);

	if (readed == 0 || fn_isline(buffer))
	{
		char *line = fn_crop(buffer);
		char *remain = fn_remain(buffer);
		fn_secfree(&buffer);
		buffer = remain;
		remain = NULL;
		return (line);
	}
	return (get_next_line(fd));
}


