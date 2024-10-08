/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:54:36 by apintus           #+#    #+#             */
/*   Updated: 2024/10/08 16:19:05 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Version colorer sans texture
// void	rays_render(t_data *data)
// {
// 	const int	slice_width = data->win_width / data->ray_count;
// 	int			i;
// 	t_ray		*ray;
// 	float		slice_height;
// 	int			color;
// 	t_vector2_d	tl;
// 	t_vector2_d	br;

// 	i = 0;
// 	while(i < data->ray_count)
// 	{
// 		ray = &data->ray_array[i];
// 		if (ray->perp_len == -1)
// 			continue;
// 		slice_height = 1.0f / ray->perp_len;
// 		slice_height *= data->win_height;
// 		slice_height *= 2;
// 		if (ray->side_hit == 0) // SOUTH
// 			color = BLUE;
// 		else if (ray->side_hit == 1) // NORD
// 			color = RED;
// 		else if (ray->side_hit == 2) // EAST
// 			color = YELLOW;
// 		else
// 			color = GREEN; // West
// 		tl.x = i * slice_width;
// 		tl.y = data->win_height / 2 - slice_height / 2;
// 		br.x = (i + 1) * slice_width;
// 		br.y = data->win_height / 2 + slice_height / 2;
// 		draw_rect_color(data, tl, br, color);
// 		i++;
// 	}
// }

// AVANT NORM
// void	rays_render(t_data *data)
// {
// 	const int			slice_width = data->win_width / data->ray_count;
// 	t_ray_render_vars	v;

// 	v.i = 0;
// 	while (v.i < data->ray_count)
// 	{
// 		v.ray = &data->ray_array[v.i];
// 		if (v.ray->len == -1)
// 			continue ;
// 		v.slice_height = (float)(data->win_height / v.ray->perp_len);
// 		v.tl.x = v.i * slice_width;
// 		v.tl.y = data->win_height / 2 - v.slice_height / 2;
// 		v.br.x = v.i * slice_width + slice_width;
// 		v.br.y = data->win_height / 2 + v.slice_height / 2;
// 		v.texture = &data->text[v.ray->side_hit];
// 		v.tex_x = get_tex_x(data, v.ray, v.texture);
// 		v.tex_y = 0;
// 		v.step = v.texture->height_img / v.slice_height;
// 		v.y = v.tl.y;
// 		while (v.y < v.br.y)
// 		{
// 			if (v.y >= 0 && v.y < data->win_height)
// 			{
// 				v.color = get_text_pixel(v.texture, v.tex_x, v.tex_y);
// 				v.x = v.tl.x;
// 				while (v.x < v.br.x)
// 				{
// 					my_mlx_pixel_put(data, v.x, v.y, v.color);
// 					v.x++;
// 				}
// 			}
// 			v.tex_y += v.step;
// 			v.y++;
// 		}
// 		v.i++;
// 	}
// }

void	render_column(t_data *data, t_ray_render_vars *v)
{
	while (v->y < v->br.y)
	{
		if (v->y >= 0 && v->y < data->win_height)
		{
			v->color = get_text_pixel(v->texture, v->tex_x, v->tex_y);
			v->x = v->tl.x;
			while (v->x < v->br.x)
			{
				my_mlx_pixel_put(data, v->x, v->y, v->color);
				v->x++;
			}
		}
		v->tex_y += v->step;
		v->y++;
	}
}

void	render_single_ray(t_data *data, t_ray *ray, int i, int slice_width)
{
	t_ray_render_vars	v;

	v.slice_height = (float)(data->win_height / ray->perp_len);
	v.tl.x = i * slice_width;
	v.tl.y = data->win_height / 2 - v.slice_height / 2;
	v.br.x = i * slice_width + slice_width;
	v.br.y = data->win_height / 2 + v.slice_height / 2;
	v.texture = &data->text[ray->side_hit];
	v.tex_x = get_tex_x(data, ray, v.texture);
	v.tex_y = 0;
	v.step = v.texture->height_img / v.slice_height;
	v.y = v.tl.y;
	render_column(data, &v);
}

void	rays_render(t_data *data)
{
	const int	slice_width = data->win_width / data->ray_count;
	int			i;
	t_ray		*ray;

	i = 0;
	while (i < data->ray_count)
	{
		ray = &data->ray_array[i];
		if (ray->len != -1)
			render_single_ray(data, ray, i, slice_width);
		i++;
	}
}
