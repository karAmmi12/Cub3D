/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloriage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:27:38 by apintus           #+#    #+#             */
/*   Updated: 2024/10/02 18:33:31 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// GARDER Fct pour dessiner un pixel dans l image (plus rapide que pixel un par un)
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= data->win_width || y >= data->win_height)
		return ;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// visu 2d
void	my_mlx_pixel_put2(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= data->win_width || y >= data->win_height)
		return ;

	dst = data->addr2 + (y * data->line_length2 + x * (data->bits_per_pixel2 / 8));
	*(unsigned int *)dst = color;
}

// visu 2d
void	draw_rect_color2(t_data *data, t_vector2_d top_left, t_vector2_d bottom_right, int color)
{
	int	x;
	int	y;

	x = top_left.x;
	y = top_left.y;
	while (y < bottom_right.y)
	{
		while (x < bottom_right.x)
		{
			my_mlx_pixel_put2(data, x, y, color);
			x++;
		}
		x = top_left.x;
		y++;
	}
}

// GARDER fct pour dessiner les rectangle de couleur
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

// GARDER fct pour dessiner le sol et le plafond (A MODIFIER NORM)
void	floor_and_ceiling(t_data *data)
{
	int		floor_color = rgb_to_mlx(0, data->fileinfo.floor[0], data->fileinfo.floor[1], data->fileinfo.floor[2]);
	int		ceiling_color = rgb_to_mlx(0, data->fileinfo.celling[0], data->fileinfo.celling[1], data->fileinfo.celling[2]);
	int		half_height = data->win_height / 2;
	int		*buffer;
	int		y;
	int		x;

	// Allouer un buffer temporaire pour une ligne
	buffer = (int *)malloc(data->win_width * sizeof(int));
	if (!buffer)
		return;

	// Remplir le buffer avec la couleur du plafond
	x = 0;
	while(x < data->win_width)
	{
		buffer[x] = ceiling_color;
		x++;
	}
	// Copier le buffer dans la moitié supérieure de l'image
	y = 0;
	while (y < half_height)
	{
		ft_memcpy(data->addr + y * data->line_length, buffer, data->win_width * sizeof(int));
		y++;
	}
	// Remplir le buffer avec la couleur du sol
	x =	0;
	while (x < data->win_width)
	{
		buffer[x] = floor_color;
		x++;
	}
	// Copier le buffer dans la moitié inférieure de l'image
	y = half_height;
	while (y < data->win_height)
	{
		ft_memcpy(data->addr + y * data->line_length, buffer, data->win_width * sizeof(int));
		y++;
	}
	// Libérer le buffer temporaire
	free(buffer);
}
