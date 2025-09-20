# include "get_next_line.h"

size_t	fn_strlen(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
		++i;
	return (i);
}

int	fn_isline(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	*fn_calloc(size_t count, size_t size)
{
	size_t		i;
	char	*allocated;

	allocated = malloc(count * size);
	if (allocated == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		allocated[i] = 0;
		i++;
	}
	return ((void *) allocated);
}

int	fn_cropidx(char	*buffer)
{
	size_t	idx;

	idx = 0;
	while (buffer[idx])
	{
		if (buffer[idx] == '\n')
			return (idx);
		++idx;
	}
	return (idx);
}

void	*fn_secfree(char **buffer)
{
	if (*buffer != NULL)
		free(buffer);
	*buffer = NULL;
	return buffer;
}
