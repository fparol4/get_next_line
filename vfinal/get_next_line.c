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
#include <string.h>

size_t	fn_strlen(char *buffer)
{
	int	i;

	if (buffer == NULL)
		return (0);
	i = 0;
	while (buffer[i])
		++i;
	return (i);
}

int	fn_isline(char *buffer)
{
	int	i;

	if (buffer == NULL)
		return (0);
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
	int		i;
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

char	*fn_string(char *source, size_t size)
{
	size_t	i;
	size_t	len;
	char	*str;

	len = fn_strlen(source);
	if (len > size)
		len = size;
	str = fn_calloc(len, sizeof(char));
	i = 0;
	while (i < len)
	{
		str[i] = source[i];
		i++;
	}
	return (str);
}

int	fn_cropidx(char	*buffer)
{
	size_t	idx;

	if (fn_strlen(buffer) == 0)
		return (0);
	while (buffer[idx])
	{
		if (buffer[idx] == '\n')
			return (idx);
		++idx;
	}
	return (idx);
}

// int	main(){}
