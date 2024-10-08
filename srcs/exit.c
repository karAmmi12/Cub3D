/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:06:40 by apintus           #+#    #+#             */
/*   Updated: 2024/10/08 15:37:37 by apintus          ###   ########.fr       */
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
	if (data->info.copy_map)
	{
		while (data->info.copy_map[i])
		{
			free(data->info.copy_map[i]);
			i++;
		}
		free(data->info.copy_map);
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
	if (data->info.north)
		free(data->info.north);
	if (data->info.south)
		free(data->info.south);
	if (data->info.east)
		free(data->info.east);
	if (data->info.west)
		free(data->info.west);
	if (data->info.file)
	{
		while (data->info.file[i])
		{
			free(data->info.file[i]);
			i++;
		}
		free(data->info.file);
	}
	clean_map_and_copy(data);
	free(data);
	exit(exit_code);
}

int	close_game(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	clean_exit(data, 0);
	return (0);
}
