#ifndef GET_NEXT_LINE_H

# include <stdio.h>

# define GET_NEXT_LINE_H

/* required-libs */
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

/* get_next_line_utils.c */
size_t	fn_strlen(char *buffer);
int		fn_isline(char *buffer);
void	*fn_calloc(size_t count, size_t size);
char	*fn_string(char *source, size_t size);
int		fn_cropidx(char	*buffer);

/* get_next_line.c */
char	*fn_concat(char *buffer, char *chunk);
char	*fn_crop(char *buffer);
char	*fn_remain(char	*buffer);
char	*get_next_line(int fd);

#endif
