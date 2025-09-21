/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparola <fparola@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:53:04 by fparola           #+#    #+#             */
/*   Updated: 2025/09/06 18:53:04 by fparola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void panic(char *s) { printf("[ERROR] - %s\n", s); exit(1); }

int	f_cropidx(char *buffer)
{
	int	i;	

	if (buffer == NULL)
		return (0);
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

char	*f_mvcursor(char *buffer)
{
	int		crop_idx;
	int		size_r;
	char	*buffer_r;

	if (buffer == NULL)
		return (NULL);
	crop_idx = f_cropidx(buffer);
	size_r = f_strlen(buffer + crop_idx + 1);
	if (size_r == 0) {
		free(buffer);
		return (NULL);
	}
	buffer_r = malloc ((size_r + 1) * sizeof(char));
	if (buffer_r == NULL)
		return (NULL);
	f_strlcpy(buffer_r, buffer + crop_idx + 1, size_r + 1);
	free(buffer);
	return (buffer_r);
}

char	*f_extract_line(char *buffer)
{
	int		crop_idx;
	char	*buffer_l;

	if (buffer == NULL)
		return (NULL);
	crop_idx = f_cropidx(buffer);
	buffer_l = malloc ((crop_idx + 1) * sizeof(char));
	if (buffer_l == NULL)
		return (NULL);
	// +2 => 1 \0 + \n (the char itself)
	f_strlcpy(buffer_l, buffer, crop_idx + 1);
	return (buffer_l);
}

char	*get_next_line(int fd)
{
	char		*chunk;
	char		*line;
	static char	*buffer;
	int			read_bytes;

	chunk = (char *) malloc (BUFFER_SIZE * sizeof(char));
	if (chunk == NULL)
		return (NULL);
	read_bytes = read(fd, chunk, BUFFER_SIZE);
	if (read_bytes == -1)
		return (NULL);
	chunk[read_bytes] = '\0';
	buffer = f_concat(buffer, chunk);
	if (buffer == NULL)
		return (NULL);
	// printf("<BUFFER> %s@\n", buffer);
	if (read_bytes == 0 || f_search(buffer, '\n'))
	{
		line = f_extract_line(buffer);
		buffer = f_mvcursor(buffer);
		// printf("<LINE> %s@\n", line);
		// printf("<REMAINING> %s@\n", buffer);
		// panic("STOP");
		return (line);
	}
	return (get_next_line(fd));
}

// int main(void) {
// 	int file = open(FILE_NAME, O_RDWR);
//
// 	for (int i = 1; i <= 5; i++) {
// 		char *line = ft_get_next_line(file);
// 		printf("EXTRACTED: %s@\n", line);
// 		free(line);
// 	}
//
// 	close(file);
// 	return 0;
// }
