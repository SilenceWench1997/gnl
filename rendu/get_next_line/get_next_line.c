#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int ft_strlen(char *s)
{
	int i = 0;
	if(!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

// char *ft_strjoin(char *s1, char *s2)
// {
// 	int len;
// 	int i = 0;
// 	int j = 0;
// 	char *str;

// 	if (!s1)
// 	{
// 		s1 = (char *)malloc(1 * sizeof(char));
// 		s1[0] = '\0';
// 	}
// 	if (!s1 || !s2)
// 		return (NULL);

// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	str = (char *)malloc(len * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		str[i + j] = s2[j];
// 		j++;
// 	}
// 	str[i + j] = '\0';
// 	return (str);
// }
void	ft_free(char *s, int i)
{
	while (i-- > 0)
		s--;
	free (s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	size_t	step;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	step = 0;
	str = (char *)malloc((len + 1) * sizeof (char));
	if (!str)
		return (NULL);
	while (*s1)
		str[step++] = *s1++;
	ft_free(s1, step);
	while (*s2)
		str[step++] = *s2++;
	str[step] = '\0';
	return (str);
}
int ft_strchr(char *s, char c)
{
	int i = 0;
	if (!s)
		return (0);
	while(s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*before_nl(char *start_buf)
{
	int		i;
	char	*line;

	if (!start_buf || !start_buf[0])
		return (NULL);
	i = 0;
	while (start_buf[i] && start_buf[i] != '\n')
		i++;
	if (start_buf[i] == '\n')
		i++;
	line = (char *)malloc(i + 1 * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (start_buf[i] && start_buf[i] != '\n')
	{
		line[i] = start_buf[i];
		i++;
	}
	if (start_buf[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

// char *before_nl(char *line)
// {
// 	int i = 0;
// 	char *before_nl;

// 	if (!line || !line[0])
// 		return (NULL);

// 	while(line[i] != '\n' && line[i])
// 		i++;
// 	i += (line[i] == '\n');
// 	before_nl = (char *)malloc((i + 1) * sizeof(char));
// 	if(!before_nl)
// 		return (NULL);
// 	i = 0;
// 	while(line[i] && line[i] != '\n')
// 	{
// 		before_nl[i] = line[i];
// 		i++;
// 	}
// 	if(line[i] == '\n')
// 		before_nl[i++] = '\n';
// 	before_nl[i] = '\0';
// 	return (before_nl);
// }

char	*after_nl(char *start_line)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	while (start_line[i] && start_line[i] != '\n')
		i++;
	if (start_line[i] == '\0')
	{
		free (start_line);
		return (NULL);
	}
	i += (start_line[i] == '\n');
	new_line = (char *)malloc(1 + ft_strlen(start_line) - i * sizeof(char));
	if (!new_line)
		return (NULL);
	while (start_line[i + j])
	{
		new_line[j] = start_line[i + j];
		j++;
	}
	new_line[j] = '\0';
	free (start_line);
	return (new_line);
}

// char *after_nl(char *line)
// {
// 	int i = 0;
// 	int j = 0;
// 	char *after_nl;

// 	while(line[i] && line[i] != '\n')
// 		i++;
// 	if (line[i] == '\0')
// 	{
// 		free(line);
// 		return (NULL);
// 	}
// 	i += (line[i] == '\n');
// 	after_nl = (char *)malloc(1 + ft_strlen(line) - i * sizeof(char));
// 	if(!after_nl)
// 		return (NULL);
// 	while (line[i + j])
// 	{
// 		after_nl[j] = line[i + j];
// 		j++;
// 	}
// 	after_nl[j] = '\0';
// 	free(line);
// 	return (after_nl);
// }

char	*get_next_line(int fd)
{
	char			*line_buf;
	int				byte;
	static char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	byte = 1;
	line_buf = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!line_buf)
		return (NULL);
	while (byte != 0 && (!(ft_strchr(line, '\n'))))
	{
		byte = read (fd, line_buf, BUFFER_SIZE);

		if (byte == -1)
		{
			free(line_buf);
			return (NULL);
		}
		line_buf[byte] = '\0';
		line = ft_strjoin(line, line_buf);
	}
	free(line_buf);
	line_buf = before_nl(line);
	line = after_nl(line);
	return (line_buf);
}

// char *get_next_line(int fd)
// {
// 	if(fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);

// 	static char *line;
// 	char *buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if(!buffer)
// 		return (NULL);
// 	int byte = 1;

// 	while(byte != 0 && (!ft_strchr(line, '\n')))
// 	{
// 		byte = read(fd, buffer, BUFFER_SIZE);
// 		if (byte < 0)
// 		{
// 			free(buffer);
// 			return (NULL);
// 		}
// 		buffer[byte] = '\0';
// 		line = ft_strjoin(line, buffer);
// 	}
// 	free(buffer);
// 	buffer = before_nl(line);
// 	line = after_nl(line);
// 	return (buffer);
// }

// int main()
// {
// 	int fd = open("text.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// }
