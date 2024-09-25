/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:43:00 by apintus           #+#    #+#             */
/*   Updated: 2024/09/25 15:47:25 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	init_tab(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	data->tab_height = 15;
	data->tab_width = 20;
	data->tab = malloc(sizeof(int *) * data->tab_height);
	if (data->tab == NULL)
		return (1);
	while (y < data->tab_height)
	{
		data->tab[y] = malloc(sizeof(int) * data->tab_width);
		if (data->tab[y] == NULL)
			return (1);
		while (x < data->tab_width)
		{
			if (x == 0 || y == 0 || x == data->tab_width - 1 || y == data->tab_height - 1)
				data->tab[y][x] = 1;
			else
				data->tab[y][x] = 0;
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

void	draw_rect_color(t_data *data, t_vector2_d top_left, t_vector2_d bottom_right, int color)
{
	int	x;
	int	y;

	x = top_left.x;
	y = top_left.y;
	while (y < bottom_right.y)
	{
		while (x < bottom_right.x)
		{
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		x = top_left.x;
		y++;
	}
}

void	print_grind(t_data *data)
{
	int	x;
	int	y;
	t_vector2_d top_left;
	t_vector2_d bottom_right;

	x = 0;
	y = 0;
	while (y < data->tab_height)
	{
		while (x < data->tab_width)
		{
			top_left.x = x * data->cell_size;
			top_left.y = y * data->cell_size;
			bottom_right.x = top_left.x + data->cell_size;
			bottom_right.y = top_left.y + data->cell_size;
			if (data->tab[y][x] == 1)
				draw_rect_color(data, top_left, bottom_right, PINK);
			else
				draw_rect_color(data, top_left, bottom_right, BLACK);
			x++;
		}
		x = 0;
		y++;
	}
}

void	set_grid_cell(t_data *data, int x, int y)
{
	t_vector2_d	tab_pos;

	tab_pos.x = x / data->cell_size;
	tab_pos.y = y / data->cell_size;
	if (x < 0 || y < 0 || tab_pos.x >= data->tab_width || tab_pos.y >= data->tab_height)
		return ;
	if (data->mouse_button == LMB)
		data->tab[tab_pos.y][tab_pos.x] = 1;
	else if (data->mouse_button == RMB)
		data->tab[tab_pos.y][tab_pos.x] = 0;
	printf("tab[%d][%d] = %d\n", (int)tab_pos.y, (int)tab_pos.x, data->tab[(int)tab_pos.y][(int)tab_pos.x]);
}

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        my_mlx_pixel_put(data, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

t_vector2_f	dda(t_data *data, t_vector2_f dest)
{
	t_vector2_d	origin;

	origin.x = data->tab_width * data->cell_size / 2;
	origin.y = data->tab_height * data->cell_size / 2;
}

int perform_raycasting(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	print_grind(data);
	int	center_x = data->tab_width * data->cell_size / 2;
	int	center_y = data->tab_height * data->cell_size / 2;
	draw_line(data, center_x, center_y, data->mouse_x, data->mouse_y, WHITE);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
