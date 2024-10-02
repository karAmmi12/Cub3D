/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:33:30 by apintus           #+#    #+#             */
/*   Updated: 2024/10/02 11:44:09 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// tab fictif a MODIFIER pour s adapter a la map
// int	init_tab(t_data *data)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	data->tab_height = 15;
// 	data->tab_width = 20;
// 	data->tab = malloc(sizeof(int *) * data->tab_height);
// 	if (data->tab == NULL)
// 		return (1);
// 	while (y < data->tab_height)
// 	{
// 		data->tab[y] = malloc(sizeof(int) * data->tab_width);
// 		if (data->tab[y] == NULL)
// 			return (1);
// 		while (x < data->tab_width)
// 		{
// 			if (x == 0 || y == 0 || x == data->tab_width - 1 || y == data->tab_height - 1)
// 				data->tab[y][x] = 1;
// 			else
// 				data->tab[y][x] = 0;
// 			x++;
// 		}
// 		x = 0;
// 		y++;
// 	}
// 	return (0);
// }

int init_tab(t_data *data, char **map, int map_height, int map_width)
{
    int x, y;

    data->tab_height = map_height;
    data->tab_width = map_width;
    data->tab = malloc(sizeof(int *) * data->tab_height);
    if (data->tab == NULL)
        return (1);

    for (y = 0; y < data->tab_height; y++)
    {
        data->tab[y] = malloc(sizeof(int) * data->tab_width);
        if (data->tab[y] == NULL)
            return (1);

        for (x = 0; x < data->tab_width; x++)
        {
            if (map[y][x] == '1')
                data->tab[y][x] = 1;
            else if (map[y][x] == '0')
                data->tab[y][x] = 0;
			else // debug
			{
				printf("x= %d, y= %d\n", x, y);
				data->tab[y][x] = 0;
			}
        }
    }
    return (0);
}

void	init_rays(t_data *data)
{
	int		i;
	double	angle_step;

	i = 0;
	data->ray_count = RAY_COUNT;
	data->view_dst = RENDER_DISTANCE * data->cell_size;
	data->ray_array = malloc(sizeof(t_ray) * data->ray_count);
	if (data->ray_array == NULL)
		exit_read(data, "Error: malloc failed\n");
	angle_step = FOV_ANGLE / data->ray_count;
	while (i < data->ray_count)
	{
		data->ray_array[i].angle = -FOV_ANGLE / 2 + i * angle_step;
		i++;
	}
	data->ray_angles = malloc(sizeof(float) * data->ray_count);
	if (data->ray_angles == NULL)
		exit_read(data, "Error: malloc failed\n");
}

void	init_player(t_data *data)
{
	// data->player.pos.x = (float)data->tab_width * (float)data->cell_size / 2.0f;
	// data->player.pos.y = (float)data->tab_height * (float)data->cell_size / 2.0f;
	// printf("player pos x: %f, y: %f\n", data->player.pos.x, data->player.pos.y);
	data->player.pos.x = data->pos_x * data->cell_size + data->cell_size / 2;
	data->player.pos.y = data->pos_y * data->cell_size + data->cell_size / 2;
	if (data->fileinfo.copy_map[(int)data->pos_y][(int)data->pos_x] == 'N')
	{
		data->player.dir.x = 0;
		data->player.dir.y = 1; // NORTH
	}
	else if (data->fileinfo.copy_map[(int)data->pos_y][(int)data->pos_x] == 'S')
	{
		data->player.dir.x = 0;
		data->player.dir.y = -1; // SOUTH
	}
	else if (data->fileinfo.copy_map[(int)data->pos_y][(int)data->pos_x] == 'E')
	{
		data->player.dir.x = 1; // east
		data->player.dir.y = 0;
	}
	else if (data->fileinfo.copy_map[(int)data->pos_y][(int)data->pos_x] == 'W')
	{
		data->player.dir.x = -1; // west
		data->player.dir.y = 0;
	}
}

// void	init_player(t_data *data)
// {
// 	data->player.pos.x = 400;
// 	data->player.pos.y = 400;
// 	data->player.dir.x = 0;
// 	data->player.dir.y = -1;
// }

void	print_tab(int **tab, int height, int width)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			printf("%d", tab[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	init_game(t_data *data)
{
	init_map(data);
	init_rays(data);
	init_tab(data ,data->fileinfo.copy_map, data->mapHeight, data->mapWidth);
	// init_tab(data);
	print_tab(data->tab, data->tab_height, data->tab_width); //debug
	init_player(data);
}
