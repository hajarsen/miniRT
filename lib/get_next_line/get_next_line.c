#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static int	position = 0;
	static int	nbr_read = 0;
	static char	buffer[BUFFER_SIZE];
	char		line[MAX_LINE_SIZE];
	int			i;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	i = 0;
	while (1)
	{
		if (position >= nbr_read)
		{
			nbr_read = read(fd, buffer, BUFFER_SIZE);
			position = 0;
			if (nbr_read <= 0)
				break ;
		}
		line[i] = buffer[position];
		position++;
		i++;
		if (buffer[position - 1] == '\n') 
			break ;
		if (i >= MAX_LINE_SIZE - 1) 
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}