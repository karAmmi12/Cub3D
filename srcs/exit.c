/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:06:40 by apintus           #+#    #+#             */
/*   Updated: 2024/08/22 17:33:17 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_read(t_data *data, char *str)
{
	ft_putstr_fd(str, 2);
	clean_exit(data, 1);
}

void	clean_map_and_copy(t_data *data)
{
	int	i;

	i = 0;
	if (data->fileinfo.copy_map)
	{
		while (data->fileinfo.copy_map[i])
		{
			free(data->fileinfo.copy_map[i]);
			i++;
		}
		free(data->fileinfo.copy_map);
	}
	if (data->map)
	{
		i = 0;
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
}

void	clean_exit(t_data *data, int exit_code)
{
	int	i;

	i = 0;
	if (data->fileinfo.north)
		free(data->fileinfo.north);
	if (data->fileinfo.south)
		free(data->fileinfo.south);
	if (data->fileinfo.east)
		free(data->fileinfo.east);
	if (data->fileinfo.west)
		free(data->fileinfo.west);
	if (data->fileinfo.file)
	{
		while (data->fileinfo.file[i])
		{
			free(data->fileinfo.file[i]);
			i++;
		}
		free(data->fileinfo.file);
	}
	clean_map_and_copy(data);
	free(data);
	exit(exit_code);
}
