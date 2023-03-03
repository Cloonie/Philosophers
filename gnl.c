#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

char *get_next_line(int fd);

#endif

#include "get_next_line.h"

char *get_next_line(int fd)
{
	int i = 0;
	int rd = 0;
	char c;
	char *buffer = malloc[10000];

	if (BUFFER_SIZE <= 0)
	{
		free(buffer);
		return(NULL);
	}
	while ((rd = read(fd, &c, BUFFER_SIZE - BUFFER_SIZE + 1)) > 0)
	{
		buffer[i++] = c;
		if (c == '\n')
			break ;
	}
	if (!buffer[i - 1] && !fd || fd == -1)
	{
		free(buffer);
		return (NULL);
	}
	buffer[i] = '\0';
	return(buffer);
}