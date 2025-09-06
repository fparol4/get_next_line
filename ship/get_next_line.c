#include "get_next_line.h"
#include <stddef.h>

#define FILE_NAME "text.txt"

int		f_cropidx(char *buffer)
{
	int i;	

	i = 0;
	while (buffer && buffer[i])
	{
		if (buffer[i] == '\n')
			break;
		i++;
	}
	return (i);
}

char	*f_mvcursor(char *buffer)
{
	int		remaining_s;
	int		crop_idx;
	char	*buffer_u;

	crop_idx = f_cropidx(buffer);
	if (!crop_idx)
		return (NULL);

	remaining_s = f_strlen(buffer + crop_idx + 1);
	if (!remaining_s)
	{
		free(buffer);
		return (NULL);
	}

	buffer_u = malloc((remaining_s + 1) * sizeof(char));
	if (!buffer_u)
		panic("MALLOC CURSOR");

	f_strlcpy(buffer_u, buffer + crop_idx + 1, remaining_s + 1);
	free(buffer);
	return (buffer_u);
}

char	*f_extract_line(char *buffer)
{
	int		crop_idx;
	char	*buffer_l;
	
	crop_idx = f_cropidx(buffer);
	if (crop_idx == 0)
		return (NULL);

	buffer_l = malloc ((crop_idx + 1) * sizeof(char));
	if (!buffer_l)
		panic("MALLOC LINE");

	f_strlcpy(buffer_l, buffer, (crop_idx + 1));
	return (buffer_l);
}

char *ft_get_next_line(int fd)
{
	int			read_bytes;
	char		*chunk;
	char		*line;
	static char	*buffer;

	chunk = (char *) malloc (BUFFER_SIZE * sizeof(char));
	if (!chunk)
		panic("chunk cannot be allocated");

	read_bytes = read(fd, chunk, 12);
	if (read_bytes == -1)
		panic("READING FILE");
	chunk[read_bytes] = '\0';

	buffer = f_concat(buffer, chunk);
	if (read_bytes == 0 || f_search(buffer, '\n'))
	{
		line = f_extract_line(buffer);
		buffer = f_mvcursor(buffer);
		printf("BF: '%s'\n", buffer);
		return (line);
	}

	return (ft_get_next_line(fd));
}

int main(void) {
	int file = open(FILE_NAME, O_RDWR);
	if (!file)
		panic("READING FILE");
	for (int i = 1; i <= 3; i++) {
		char *line = ft_get_next_line(file);
		printf("LINE: %s\n", line);
		// panic("42");
		free(line);
	}
	close(file);
	return -1;
}
