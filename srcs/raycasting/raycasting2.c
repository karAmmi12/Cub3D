/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:48:36 by apintus           #+#    #+#             */
/*   Updated: 2024/10/04 19:14:17 by apintus          ###   ########.fr       */
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

void rays_render(t_data *data)
{
  const int slice_width = data->win_width / data->ray_count;

  for (int i = 0; i < data->ray_count; i++)
  {
    t_ray *ray = &data->ray_array[i];

    if (ray->len == -1)
      continue;

  	float slice_height = (float)(data->win_height / ray->perp_len);
    t_vector2_d tl = {i * slice_width, data->win_height / 2 - slice_height / 2};
    t_vector2_d br = {i * slice_width + slice_width, data->win_height / 2 + slice_height / 2};

    t_text *texture = &data->text[ray->side_hit]; // Reference to the texture according on side_hit

    int tex_x = get_tex_x(data, ray, texture, i);
    double tex_y = 0;

    double step = texture->height_img / slice_height;

    for (int y = tl.y; y < br.y; y++)
    {
      if (y >= 0 && y < data->win_height)
      {
        int color = get_text_pixel(texture, tex_x, tex_y);

        for (int x = tl.x; x < br.x; x++)
          my_mlx_pixel_put(data, x, y, color);
      }
      tex_y += step;
    }
  }
}


