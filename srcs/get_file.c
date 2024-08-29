/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:38:40 by apintus           #+#    #+#             */
/*   Updated: 2024/08/29 17:27:55 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strdup_n(const char *s)
{
	size_t	i;
	size_t	len;
	char	*str;

	len = ft_strlen(s);
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (s[i] == '\n' && i == len - 1)
			str[i] = '\0';
		else
			str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	count_lines( char *filename)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = 0;
	line = get_next_line(fd, 0);
	while (line != NULL)
	{
		lines++;
		free(line);
		line = get_next_line(fd, 0);
	}
	close(fd);
	return (lines);
}

void	read_and_copy_lines(t_data *data, int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd, 0);
	while (line != NULL)
	{
		if (line[0] == '\n')
			data->fileinfo.file[i] = ft_strdup("\n");
		else
			data->fileinfo.file[i] = ft_strdup_n(line);
		if (data->fileinfo.file[i] == NULL)
			exit_read(data, "Malloc error\n");
		free(line);
		i++;
		line = get_next_line(fd, 0);
	}
	data->fileinfo.file[i] = NULL;
}

int	copy_file(t_data *data, char *filename)
{
	int	fd;
	int	line_count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_read(data, "Error: File not found\n");
	line_count = count_lines(filename);
	if (line_count < 0)
		exit_read(data, "Error: Could not count lines\n");
	data->fileinfo.file = malloc((line_count + 1) * sizeof(char *));
	if (data->fileinfo.file == NULL)
		exit_read(data, "Malloc error\n");
	read_and_copy_lines(data, fd);
	close(fd);
	return (1);
}
