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

	i = 0;
	while (buffer && buffer[i])
	{
		if (buffer[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

char	*f_mvcursor(char *buffer)
{
	int		remaining_s;
	int		crop_idx;
	char	*buffer_u;

	if (buffer == NULL) 
		return (NULL);
	crop_idx = f_cropidx(buffer);
	remaining_s = f_strlen(buffer + crop_idx + 1);
	if (remaining_s == 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer_u = malloc((remaining_s + 1) * sizeof(char));
	if (buffer_u == NULL)
		return (NULL);
	f_strlcpy(buffer_u, buffer + crop_idx + 1, remaining_s + 1);
	free(buffer);
	return (buffer_u);
}

char	*f_extract_line(char *buffer)
{
	int		crop_idx;
	char	*buffer_l;

	if (buffer == NULL)
		return (NULL);
	crop_idx = f_cropidx(buffer);
	if (crop_idx == 0 && f_strlen(buffer) == 0)
		return (NULL);
	buffer_l = malloc ((crop_idx + 1) * sizeof(char));
	if (!buffer_l)
		return (NULL);
	f_strlcpy(buffer_l, buffer, (crop_idx + 2));
	return (buffer_l);
}

char	*ft_get_next_line(int fd)
{
	int			read_bytes;
	char		*chunk;
	char		*line;
	static char	*buffer;

	chunk = (char *) malloc (BUFFER_SIZE * sizeof(char));
	if (chunk == NULL)
		return (NULL);
	read_bytes = read(fd, chunk, BUFFER_SIZE);
	if (read_bytes == -1)
	{
		if (buffer)
			free(buffer);
		return (NULL);
	}
	chunk[read_bytes] = '\0';
	buffer = f_concat(buffer, chunk);
	if (read_bytes == 0 || f_search(buffer, '\n'))
	{
		line = f_extract_line(buffer);
		buffer = f_mvcursor(buffer);
		return (line);
	}
	return (ft_get_next_line(fd));
}

int main(void) {
	int file = open(FILE_NAME, O_RDWR);

	for (int i = 1; i <= 9; i++) {
		char *line = ft_get_next_line(file);
		printf("R: %s \n--\n", line);
		free(line);
	}

	close(file);
	return 0;
}
