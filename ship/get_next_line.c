#include "get_next_line.h"

#define FILE_NAME "text.txt"

char	*ft_mvcursor(char *buffer, size_t n)
{
	int		size_r; 
	int		size_b;
	char	*buffer_u;

	size_b = f_strlen(buffer);
	size_r = size_b - n; // SIZE_BUFFER - IDX 
	buffer_u = malloc((size_r) * sizeof(char));
	if (!buffer_u)
		panic("cannot allocate");
	printf("B: %s", buffer);
	f_strlcpy(buffer_u, buffer + n, n);
	printf("CURSOR: %s\n", buffer_u);
	panic("here");
}

char *ft_get_next_line(int fd)
{
	int			read_bytes;
	char		*chunk;
	char		*p_linebreak;
	static char	*buffer;

	chunk = (char *) malloc (BUFFER_SIZE * sizeof(char));
	if (!chunk)
		panic("chunk cannot be allocated");

	read_bytes = read(fd, chunk, BUFFER_SIZE);
	if (read_bytes == 0)
		return (NULL);
	if (read_bytes == -1)
		panic("reading file");
	
	buffer = f_concat(buffer, chunk);
	p_linebreak = f_search(buffer, '\n');
	if (p_linebreak)
	{
		buffer = ft_mvcursor(buffer, (p_linebreak - buffer) + 1);
	}
	return buffer;
}

int main(void) {
	int file = open(FILE_NAME, O_RDWR);
	if (!file)
		panic("file cannot be readed");
	char *line = ft_get_next_line(file);
	free(line);
	close(file);
	return -1;
}
