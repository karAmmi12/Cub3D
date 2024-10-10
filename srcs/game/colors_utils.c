/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:22:57 by kammi             #+#    #+#             */
/*   Updated: 2024/10/09 12:56:41 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	rgb_to_mlx(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= data->win_width || y >= data->win_height)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_rect_color(t_data *data, t_vector2_d top_left
, t_vector2_d bottom_right, int color)
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

void	floor_and_ceiling(t_data *data)
{
	t_flo_cel_vars	v;

	v.floor_color = rgb_to_mlx(0, data->info.floor[0], data->info.floor[1],
			data->info.floor[2]);
	v.ceiling_color = rgb_to_mlx(0, data->info.celling[0],
			data->info.celling[1], data->info.celling[2]);
	v.half_height = data->win_height / 2;
	v.buffer = (int *)malloc(data->win_width * sizeof(int));
	if (!v.buffer)
		return ;
	v.x = 0;
	while (v.x++ < data->win_width - 1)
		v.buffer[v.x] = v.ceiling_color;
	v.y = 0;
	while (v.y++ < v.half_height)
		ft_memcpy(data->addr + v.y * data->line_length, v.buffer,
			data->win_width * sizeof(int));
	v.x = 0;
	while (v.x++ < data->win_width - 1)
		v.buffer[v.x] = v.floor_color;
	v.y = v.half_height;
	while (v.y++ < data->win_height)
		ft_memcpy(data->addr + v.y * data->line_length, v.buffer,
			data->win_width * sizeof(int));
	free (v.buffer);
}