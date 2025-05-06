/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:06:12 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/24 22:02:04 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	bytes_reader(int fd, void *buf, size_t count)
{
	ssize_t	read_bytes;

	read_bytes = read(fd, buf, count);
	if (read_bytes < 0)
		return (-1);
	if (read_bytes == 0)
		return (0);
	return (read_bytes);
}

static char	*join_and_free(char *line, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(line, buffer);
	if (tmp == NULL)
		return (free(line), NULL);
	free(line);
	return (tmp);
}

static char	*extract_line(char *line, char *buffer)
{
	char	*newline_char;
	size_t	line_len;
	char	*tmp;
	char	*joined_line;

	newline_char = ft_strchr(buffer, '\n');
	if (newline_char == NULL)
		return (ft_strjoin(line, buffer));
	line_len = newline_char - buffer + 1;
	tmp = malloc(sizeof(char) * (line_len + 1));
	if (tmp == NULL)
		return (free(line), NULL);
	ft_strncpy(tmp, buffer, line_len);
	tmp[line_len] = '\0';
	ft_memmove(buffer, &buffer[line_len], BUFFER_SIZE - line_len);
	buffer[BUFFER_SIZE - line_len] = '\0';
	joined_line = ft_strjoin(line, tmp);
	free(tmp);
	if (joined_line == NULL)
		return (free(line), NULL);
	free(line);
	return (joined_line);
}

static char	*read_until_needed(int fd, char *line, char *buffer)
{
	ssize_t		read_bytes;

	read_bytes = BUFFER_SIZE;
	while (read_bytes == BUFFER_SIZE)
	{
		read_bytes = bytes_reader(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			break ;
		buffer[read_bytes] = '\0';
		if (read_bytes == 0)
			break ;
		if (ft_strchr(buffer, '\n') == NULL)
		{
			line = join_and_free(line, buffer);
			buffer[0] = '\0';
			if (line == NULL)
				return (NULL);
		}
		else
			return (extract_line(line, buffer));
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = "";
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_strlen(buffer) > 0)
	{
		line = extract_line(line, buffer);
		if (ft_strchr(line, '\n') != NULL)
			return (line);
		if (line == NULL)
			return (NULL);
	}
	line = read_until_needed(fd, line, buffer);
	return (line);
}

/* int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		write(2, "Errore nella lettura\n", 21);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "Errore nell'apertura del file\n", 31);
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("[%s]", line);
		free(line);
	}
	close(fd);
	return (0);
} */