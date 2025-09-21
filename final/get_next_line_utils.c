/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparola <fparola@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:58:02 by fparola           #+#    #+#             */
/*   Updated: 2025/09/14 15:58:02 by fparola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*fn_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	size_t	total;
	void	*ptr;

	if (!nmemb || !size)
		return (malloc(1));
	if (nmemb >= ((size_t) -1 / size))
		return (NULL);
	total = nmemb * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

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

size_t	fn_isline(char *buffer)
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

size_t	fn_cropidx(char	*buffer)
{
	size_t	idx;

	if (buffer == NULL)
		return (0);
	idx = 0;
	while (buffer[idx])
	{
		if (buffer[idx] == '\n')
			return (idx);
		++idx;
	}
	return (idx);
}

void	*fn_secfree(char **buffer[], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (*buffer[i] != NULL)
		{
			free(*buffer[i]);
			*buffer[i] = NULL;
		}
		i++;
	}
	return (NULL);
}
