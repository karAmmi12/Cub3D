/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:53:00 by apintus           #+#    #+#             */
/*   Updated: 2024/10/02 14:04:12 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// VISU 2D
void	draw_square(t_data *data, int x, int y, int color)
{
	for (int i = -2; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			my_mlx_pixel_put(data, x + i, y + j, color);
		}
	}
}

// VISU 2D imprime la map
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
			if (data->tab[y][x] == 1) // VISU 2d
				draw_rect_color2(data, top_left, bottom_right, PINK);
			else
				draw_rect_color2(data, top_left, bottom_right, BLACK);
			x++;
		}
		x = 0;
		y++;
	}
}

//VISU 2D pour modfiier la map avec la souris
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
}

// VISU 2D imprimer un rayon (a supprimer)
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

//VISU 2D WTFFF SUPER MULTI RAYON JAUUU
void	bresenham(t_data *data, t_vector2_d origin, t_vector2_f dst, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	x;
	int	y;
	
	dx = abs((int)dst.x - (int)origin.x);
	dy = abs((int)dst.y - (int)origin.y);
	sx = (origin.x < dst.x) ? 1 : -1;
	sy = (origin.y < dst.y) ? 1 : -1;
	err = dx - dy;
	x = (int)origin.x;
	y = (int)origin.y;
	while (1)
	{
		// Assurez-vous que les coordonnées sont dans les limites de l'écran
		if (x >= 0 && x < data->win_width && y >= 0 && y < data->win_height)
			my_mlx_pixel_put2(data, x, y, color);
		if (x == (int)dst.x && y == (int)dst.y)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}
