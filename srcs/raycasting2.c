/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:48:36 by apintus           #+#    #+#             */
/*   Updated: 2024/09/30 14:55:52 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		if (ray->perp_len == -1) // before was len
			continue;

		slice_height = 1.0f / ray->perp_len; // before was len
		slice_height *= data->win_height;
		slice_height *= 2;
		if (i == 30)
		{
			printf("slice_height: %f\n", slice_height);
			printf("slice_width: %d\n", slice_width);
		}
		if (ray->side_hit == 0) // NOrth
			color = RED;
		else if (ray->side_hit == 1) //SOuth
			color = BLUE;
		else if (ray->side_hit == 2) // East
			color = YELLOW;
		else
			color = GREEN; // West

		tl.x = i * slice_width;
		tl.y = data->win_height / 2 - slice_height / 2;
		br.x = (i + 1) * slice_width;
		br.y = data->win_height / 2 + slice_height / 2;

		// tl.x = i * slice_width;
		// tl.y = data->win_height / 2 + slice_height / 2;
		// br.x = i * slice_width + slice_width;
		// br.y = data->win_height / 2 - slice_height / 2;
		draw_rect_color(data, tl, br, color);

		i++;
	}
}
