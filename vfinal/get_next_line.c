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

void	*fn_clean(char *buffers[], size_t size)
{
	size_t	i;	

	i = 0;
	while (i++ < size)
		free(buffers[i - 1]);
	return (NULL);
}

char	*ft_concat(char *buffer, char *chunk)
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
	s_concated = s_chunk + s_buffer + 1;
	b_concated = fn_calloc(s_concated, sizeof(char));
	if (b_concated == NULL)
		return fn_clean((char*[]){ buffer, chunk }, 2);
	i = 0;
	while (i++ < s_buffer)
		b_concated[i - 1] = buffer[i - 1];
	i = 0;
	while (i++ < s_concated)
		b_concated[i - 1] = chunk[i - 1];
	b_concated[i - 1] = '\0';
	fn_clean((char*[]){ buffer, chunk }, 2);
	return (b_concated);
}

char	*fn_movecursor(char	*buffer, char idx)
{
	if (buffer == NULL)
		return (NULL);
	return (NULL);
}

int	main() {
}
