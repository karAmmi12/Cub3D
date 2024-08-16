/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:38:40 by apintus           #+#    #+#             */
/*   Updated: 2024/08/16 14:11:57 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* void	process_line(t_data *data, char *line, int	*i)
{
	if (data->bigline == NULL)
	{
		data->bigline = ft_strdup(line);
		if (data->bigline == NULL)
			exit_read(data, "Malloc error1\n");
		data->bigline = ft_strjoin(data->bigline, "\n");
		if (data->bigline == NULL)
			exit_read(data, "Malloc error2\n");
		(*i)++;
		return ;
	}
	data->bigline = ft_strjoin(data->bigline, line);
	if (data->bigline == NULL)
		exit_read(data, "Malloc error4\n");
	data->bigline = ft_strjoin(data->bigline, "\n");
	if (data->bigline == NULL)
		exit_read(data, "Malloc error5\n");
	(*i)++;
}

int	copy_file(t_data *data, char *filename)
{
	int	fd;
	int	i;
	char	*temp;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_read(data, "Error: File not found\n");
	while (1)
	{
		temp = get_next_line(fd, 0);
		if (temp == NULL)
		{
			if (i == 0)
				exit_read(data, "Error: Empty file\n");
			break ;
		}
		process_line(data, temp, &i);
	}
	printf("BIGLINE: %s\n", data->bigline); // a supp
	data->fileinfo.file = ft_split(data->bigline, '\n');
	if (data->fileinfo.file == NULL)
		exit_read(data, "Malloc error1\n");
	free(data->bigline);
	close(fd);
	return (1);
} */


char	*ft_strdup_n(const char *s)
{
    size_t		i;
    size_t		len;
    char		*str;

    len = ft_strlen(s);
    str = (char *)malloc(sizeof(*s) * (len + 1)); // Allocate memory for the new string
    if (!str)
        return (NULL);

    i = 0;
    while (i < len)
    {
        if (s[i] == '\n' && i == len - 1) // Check if the last character is '\n'
            str[i] = '\0'; // Replace '\n' with '\0'
        else
            str[i] = s[i];
        i++;
    }
    str[i] = '\0'; // Ensure the string is null-terminated
    return (str);
}
int count_lines( char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) return -1;

    int lines = 0;
    char *line;
    while ((line = get_next_line(fd, 0)) != NULL) {
        lines++;
        free(line);
    }
    close(fd);
    return lines;
}

int copy_file(t_data *data, char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) exit_read(data, "Error: File not found\n");

    int line_count = count_lines(filename);
    if (line_count < 0) exit_read(data, "Error: Could not count lines\n");

    data->fileinfo.file = malloc((line_count + 1) * sizeof(char *));
    if (data->fileinfo.file == NULL) exit_read(data, "Malloc error\n");

    int i = 0;
    char *line;
    while ((line = get_next_line(fd, 0)) != NULL) {
        if (line[0] == '\n') {
            data->fileinfo.file[i] = ft_strdup("\n");
        } else {
            data->fileinfo.file[i] = ft_strdup_n(line);
        }
        if (data->fileinfo.file[i] == NULL) exit_read(data, "Malloc error\n");
        free(line);
        i++;
    }
    data->fileinfo.file[i] = NULL;

    close(fd);
    return 1;
}
