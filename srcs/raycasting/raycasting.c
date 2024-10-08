/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:43:00 by apintus           #+#    #+#             */
/*   Updated: 2024/10/08 16:31:26 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_vector2_d	dda(t_data *data, t_ray *ray)
{
	t_dda_vars		v;

	v.origin.x = (double)data->player.pos.x;
	v.origin.y = (double)data->player.pos.y;
	v.map = v.origin;
	v.dir.x = ray->hit_point.x - v.origin.x;
	v.dir.y = ray->hit_point.y - v.origin.y;
	if (v.dir.x == 0)
		v.delta_dist.x = 1e30;
	else
		v.delta_dist.x = fabs(1.0f / v.dir.x);
	if (v.dir.y == 0)
		v.delta_dist.y = 1e30;
	else
		v.delta_dist.y = fabs(1.0f / v.dir.y);
	if (v.dir.x < 0)
	{
		v.step.x = -1;
		v.side_dist.x = (v.origin.x - v.map.x) * v.delta_dist.x;
	}
	else
	{
		v.step.x = 1;
		v.side_dist.x = (v.map.x + 1.0f - v.origin.x) * v.delta_dist.x;
	}
	if (v.dir.y < 0)
	{
		v.step.y = -1;
		v.side_dist.y = (v.origin.y - v.map.y) * v.delta_dist.y;
	}
	else
	{
		v.step.y = 1;
		v.side_dist.y = (v.map.y + 1.0f - v.origin.y) * v.delta_dist.y;
	}
	v.ray_length = get_vector_double_len(v.origin, v.map);
	while (v.ray_length < data->view_dst * data->view_dst)
	{
		if (v.side_dist.x < v.side_dist.y)
		{
			v.side_dist.x += v.delta_dist.x;
			v.map.x += v.step.x;
			ray->perp_len = (v.side_dist.x - v.delta_dist.x) * data->cell_size;
			if (v.step.x > 0)
				ray->side_hit = 2;
			else
				ray->side_hit = 3;
		}
		else
		{
			v.side_dist.y += v.delta_dist.y;
			v.map.y += v.step.y;
			ray->perp_len = (v.side_dist.y - v.delta_dist.y) * data->cell_size;
			if (v.step.y > 0)
				ray->side_hit = 0;
			else
				ray->side_hit = 1;
		}
		v.ray_length = get_vector_double_len(v.origin, v.map);
		v.cell.x = v.map.x / data->cell_size;
		v.cell.y = v.map.y / data->cell_size;
		if (v.cell.x < 0 || v.cell.x >= data->win_width)
			continue ;
		if (v.cell.y < 0 || v.cell.y >= data->win_height)
			continue ;
		if (data->tab[v.cell.y][v.cell.x] == 1)
		{
			if (ray->side_hit == 2 || ray->side_hit == 3)
			{
				v.hit_point.x = v.map.x;
				v.hit_point.y = v.origin.y + (v.map.x - v.origin.x) * (v.dir.y / v.dir.x);
			}
			else
			{
				v.hit_point.x = v.origin.x + (v.map.y - v.origin.y) * (v.dir.x / v.dir.y);
				v.hit_point.y = v.map.y;
			}
			return (v.hit_point);
		}
	}
	return (v.map);
}


void	calculate_collisions(t_data *data)
{
	t_vector2_d	origin;
	t_vector2_d	res;
	int			i;

	origin.x = data->player.pos.x;
	origin.y = data->player.pos.y;
	i = 0;
	while (i < data->ray_count)
	{
		res = dda(data, &data->ray_array[i]);
		if (res.x != -1 && res.y != -1)
		{
			data->ray_array[i].hit_point = res;
			data->ray_array[i].len = get_vector_double_len(origin, res);
		}
		else
			data->ray_array[i].len = -1;
		bresenham(data, origin, data->ray_array[i].hit_point, YELLOW);//VISU 2D
		i++;
	}
}
void creat_rays(t_data *data)
{
	t_vector2_d origin;
	double angle;
	t_vector2_d view_dst_pos;
	int opposite_len;
	t_vector2_d opposite_vec[2];
	double increment;
	int i;
	t_vector2_d vector;

	origin.x = data->player.pos.x;
	origin.y = data->player.pos.y;
	angle = atan2(data->player.dir.y, data->player.dir.x);
	view_dst_pos.x = origin.x + data->player.dir.x * data->view_dst;
	view_dst_pos.y = origin.y + data->player.dir.y * data->view_dst;
	opposite_len = tan(degree_to_radian(FOV_ANGLE / 2)) * data->view_dst;
	opposite_vec[0] = create_vector_d_from_origin(view_dst_pos, angle + M_PI / 2, opposite_len);
	opposite_vec[1] = create_vector_d_from_origin(view_dst_pos, angle - M_PI / 2, opposite_len);
	increment = 1.0f / (data->ray_count - 1.0f);
	i = 0;
	while (i < data->ray_count)
	{
		vector = vector_d_lerp(opposite_vec[0], opposite_vec[1], increment * i);
		data->ray_array[i].angle = get_angle(origin, vector.x, vector.y);
		data->ray_array[i].hit_point = vector;
		data->ray_array[i].hit_point.y = data->tab_height * data->cell_size - data->ray_array[i].hit_point.y;
		i++;
	}
}

// GARDER fct qui boucle dans la mlx_loop_hook maiss
int perform_raycasting(t_data *data)
{
	print_grind(data);// VISU 2D
	input_key(data);
	floor_and_ceiling(data);
	creat_rays(data);
	calculate_collisions(data);
	rays_render(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win2, data->img2, 0, 0);
	return (0);
}
