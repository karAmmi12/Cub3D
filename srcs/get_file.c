/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:38:40 by apintus           #+#    #+#             */
/*   Updated: 2024/07/31 13:07:58 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	process_line(t_data *data, char *line, int	*i)
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
	data->fileinfo.file = ft_split(data->bigline, '\n');
	if (data->fileinfo.file == NULL)
		exit_read(data, "Malloc error1\n");
	free(data->bigline);
	close(fd);
	return (1);
}
