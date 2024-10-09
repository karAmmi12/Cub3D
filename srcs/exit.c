/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:06:40 by apintus           #+#    #+#             */
/*   Updated: 2024/10/09 14:13:00 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_read(t_data *data, char *str, int flag)
{
	ft_putstr_fd(str, 2);
	clean_exit(data, 1, flag);
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

void	clean_tab(t_data *data)
{
	int	i;

	i = 0;
	if (data->tab)
	{
		while (i < data->tab_height)
		{
			free(data->tab[i]);
			i++;
		}
		free(data->tab);
	}
}

void	clean_ray_array(t_data *data)
{
	if (data->ray_array)
		free(data->ray_array);
	if (data->ray_angles)
		free(data->ray_angles);
}

void	clean_info(t_data *data)
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
}

void	clean_mlx_loading_fail(t_data *data)
{
	clean_textures(data);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

void	clean_exit(t_data *data, int exit_code, int flag)
{
	if (flag == 1)
		clean_mlx_loading_fail(data);
	clean_info(data);
	clean_map_and_copy(data);
	clean_ray_array(data);
	clean_tab(data);
	free(data);
	exit(exit_code);
}

int	close_game(t_data *data)
{
	clean_textures(data);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	clean_exit(data, 0, 0);
	return (0);
}
