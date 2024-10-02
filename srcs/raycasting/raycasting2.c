/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:48:36 by apintus           #+#    #+#             */
/*   Updated: 2024/10/02 17:17:12 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rays_render(t_data *data)
{
	const int	slice_width = data->win_width / data->ray_count;
	int			i;
	t_ray		*ray;
	float		slice_height;
	int			color;
	t_vector2_d	tl;
	t_vector2_d	br;

	i = 0;
	while(i < data->ray_count)
	{
		ray = &data->ray_array[i];
		if (ray->perp_len == -1)
			continue;

		slice_height = 1.0f / ray->perp_len;
		slice_height *= data->win_height;
		slice_height *= 2;

		if (ray->side_hit == 0) // SOUTH
			color = BLUE;
		else if (ray->side_hit == 1) // NORD
			color = RED;
		else if (ray->side_hit == 2) // EAST
			color = YELLOW;
		else
			color = GREEN; // West

		tl.x = i * slice_width;
		tl.y = data->win_height / 2 - slice_height / 2;
		br.x = (i + 1) * slice_width;
		br.y = data->win_height / 2 + slice_height / 2;

		draw_rect_color(data, tl, br, color);

		i++;
	}
}
