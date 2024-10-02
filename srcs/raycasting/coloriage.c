/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloriage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:27:38 by apintus           #+#    #+#             */
/*   Updated: 2024/10/01 18:28:31 by apintus          ###   ########.fr       */
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

void	my_mlx_pixel_put2(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= data->win_width || y >= data->win_height)
		return ;

	dst = data->addr2 + (y * data->line_length2 + x * (data->bits_per_pixel2 / 8));
	*(unsigned int *)dst = color;
}

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
	int		floor_color = PURPLE;
	int		ceiling_color = GREY;
	int		half_height = data->win_height / 2;
	int		*buffer;
	int		y;

	// Allouer un buffer temporaire pour une ligne
	buffer = (int *)malloc(data->win_width * sizeof(int));
	if (!buffer)
		return;

	// Remplir le buffer avec la couleur du plafond
	for (int x = 0; x < data->win_width; x++)
		buffer[x] = ceiling_color;

	// Copier le buffer dans la moitié supérieure de l'image
	for (y = 0; y < half_height; y++)
		memcpy(data->addr + y * data->line_length, buffer, data->win_width * sizeof(int));

	// Remplir le buffer avec la couleur du sol
	for (int x = 0; x < data->win_width; x++)
		buffer[x] = floor_color;

	// Copier le buffer dans la moitié inférieure de l'image
	for (y = half_height; y < data->win_height; y++)
		memcpy(data->addr + y * data->line_length, buffer, data->win_width * sizeof(int));

	// Libérer le buffer temporaire
	free(buffer);
}
