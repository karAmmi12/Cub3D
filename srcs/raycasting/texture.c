/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:49:39 by apintus           #+#    #+#             */
/*   Updated: 2024/10/03 18:28:46 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	load_texture(t_data *data, t_text *text, char *path)
{
	printf("Loading texture: %s\n", path);
	text->img = mlx_xpm_file_to_image(data->mlx, path, &text->width_img, &text->height_img);
	if (text->img == NULL)
		return (1);
	text->text_addr = mlx_get_data_addr(text->img, &text->bits_per_pixel, &text->line_len, &text->endian);
	if (text->text_addr == NULL)
		return (1);
	return (0);
}

int	get_text_pixel(t_text *text, int x, int y)
{
	int	color;

	if (x < 0 || x >= text->width_img)
		return (0);
	if (y < 0 || y >= text->height_img)
		return (0);

	color = *(int *)(text->text_addr + (y * text->line_len) + (x * text->bits_per_pixel / 8));
	return (color);
}

t_vector2_f	create_vect_f_from_origin(t_vector2_f origin, double angle, double length)
{
	t_vector2_f	vector;

	vector.x = origin.x + cos(angle) * length;
	vector.y = origin.y + sin(angle) * length;
	return (vector);
}
int	get_angle_f(t_vector2_f origin, t_vector2_f target)
{
	double	angle;

	angle = atan2(target.y - origin.y, target.x - origin.x);
	return (angle);
}

int get_tex_x(t_data *data, t_ray *ray, t_text *texture)
{
  // Calculer la position exacte du mur touché
  double wall_hit_x;
  if (ray->side_hit == 0 || ray->side_hit == 1) // Mur horizontal (Sud, Nord)
    wall_hit_x = data->player.pos.x + ray->perp_len * cos(ray->angle);
  else // Mur vertical (Est, Ouest)
    wall_hit_x = data->player.pos.y + ray->perp_len * sin(ray->angle);

  // Calculer la position relative à la cellule
  wall_hit_x -= floor(wall_hit_x);

  // Convertir la position en coordonnées de texture
  int tex_x = (int)(wall_hit_x * (double)texture->width_img);
  if ((ray->side_hit == 0 && cos(ray->angle) > 0) || (ray->side_hit == 1 && cos(ray->angle) < 0))
    tex_x = texture->width_img - tex_x - 1;

  return tex_x;
}
