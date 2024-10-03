/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:49:39 by apintus           #+#    #+#             */
/*   Updated: 2024/10/03 17:17:44 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	load_texture(t_data *data, t_text *text, char *path)
{
	printf("Loading texture: %s\n", path);
	text->img = mlx_xpm_file_to_image(data->mlx, path, &text->width_img, &text->height_img);
	if (text->img == NULL)
		return (printf("SIUUU\n"), 1);
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
  // Calculating exact hit position
  double perp_angle = PI_2 - ray->angle + get_angle_f(data->player.pos, vector_d_to_f(data->player.view_dis_pos));
  double hit_length = ray->perp_len * data->cell_size / sin(perp_angle);
  t_vector2_f wall_x = create_vect_f_from_origin(data->player.pos, ray->angle, hit_length);

  float cell_pos;
  // Getting hit position relative to the cell
  if (ray->side_hit == 0 || ray->side_hit == 1) // Horizontal hit (Sud, Nord)
    cell_pos = wall_x.y - (int)(wall_x.y / data->cell_size) * data->cell_size;
  else // Vertical hit (Est, Ouest)
    cell_pos = wall_x.x - (int)(wall_x.x / data->cell_size) * data->cell_size;

  // Converting cell_pos to ratio and flipping if necessary
  if (ray->side_hit == 1 || ray->side_hit == 2) // Nord or Est
    cell_pos = 1.0f - cell_pos / data->cell_size;
  else // Sud or Ouest
    cell_pos = cell_pos / data->cell_size;

  int tex_x = cell_pos * texture->width_img; // Mapping ratio to texture dimension

  return tex_x;
}
