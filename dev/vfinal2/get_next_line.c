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

void	*fn_secfree(char **buffer)
{
	if (*buffer != NULL)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

char	*fn_concat(char *buffer, char *chunk)
{
	int s_buffer = fn_strlen(buffer);
	int s_chunk = fn_strlen(chunk);

	if (s_buffer == 0 && s_chunk == 0)
		return (NULL);

	char *b_concated = fn_calloc(s_buffer + s_chunk + 1, sizeof(char));
	if (b_concated == NULL)
		return fn_secfree(&b_concated);

	int i = 0;
	while (i++ < s_buffer)
		b_concated[i - 1] = buffer[i - 1];
	
	i = 0;
	while (i++ < s_chunk)
		b_concated[i - 1 + s_buffer] = chunk[i - 1];
	b_concated[i - 1 + s_buffer] = '\0';

	return (b_concated);
}

char	*fn_cropline(char *buffer, int idx)
{
	// if (idx == 0) maybe (?)

	if (buffer[idx] == '\n')
		idx++;

	char*b_line = fn_calloc(idx + 1, sizeof(char)); 
	if (b_line == NULL)
		return fn_secfree(&b_line);

	int i = 0;
	while (i++ < idx)
		b_line[i - 1] = buffer[i - 1];
	b_line[i - 1] = '\0';

	return (b_line);
}

char	*fn_movecursor(char *buffer, int idx)
{
	int s_buffer = fn_strlen(buffer);	
	if (s_buffer == 0)
		return (NULL);

	int s_remaining = fn_strlen(buffer + idx + 1);
	if (s_remaining == 0)
		return (NULL);

	char *b_remaining = fn_calloc(s_remaining + 1, sizeof(char));
	if (b_remaining == NULL)
		return fn_secfree(&b_remaining);

	int i = 0;
	while (i++ < s_remaining)
		b_remaining[i - 1] = buffer[i + idx];
	b_remaining[i - 1] = '\0';

	return b_remaining;
}

char	*get_next_line(int fd)
{
	static char *buffer;

	if (fd == 0)
		return (NULL);

	char *chunk = fn_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (chunk == NULL)
	{
		fn_secfree(&buffer);
		return (NULL);
	}

	int readed = read(fd, chunk, BUFFER_SIZE);	
	if (readed == -1)
	{
		fn_secfree(&chunk);
		fn_secfree(&buffer);
		return (NULL);
	}
	chunk[readed] = '\0';

	char *concated = fn_concat(buffer, chunk);
	fn_secfree(&buffer);
	fn_secfree(&chunk);

	if (concated == NULL)
		return (NULL);

	buffer = concated;
	concated = NULL;

	if (readed == 0 || fn_isline(buffer))
	{   
		int cropidx = fn_cropidx(buffer);
		char *line = fn_cropline(buffer, cropidx);
		char *remaining = fn_movecursor(buffer, cropidx);
		fn_secfree(&buffer);	
		buffer = remaining;
		remaining = NULL;
		return (line);
	}
	return (get_next_line(fd));
};

// int	__T_01__() {
// 	char *files[] = {
// 		"text.txt",
// 		"big_line.txt",
// 		"read_error.txt",
// 		"lines_around_10.txt"
// 	};
// 	int fd	= open(files[3], O_RDONLY);
// 	for (int i = 1; i <= 8; ++i) {
// 		char *l = get_next_line(fd);
// 		printf("L: %s$\n", l);
// 		free(l);
// 	}
// 	close(fd);
// 	return 0;
// }
//
// int	main()
// {
// 	__T_01__();
// }

