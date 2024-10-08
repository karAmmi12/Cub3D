/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:43:00 by apintus           #+#    #+#             */
/*   Updated: 2024/10/08 14:44:50 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// GARDER fct qui renvoie le point d impact du rayon
// t_vector2_f	dda(t_data *data, t_ray* ray)
// {
// 	t_vector2_d	origin;
// 	t_vector2_d	map;
// 	t_vector2_f dir;
// 	t_vector2_f	side_dist;
// 	t_vector2_f	delta_dist;
// 	t_vector2_f	step;
// 	t_vector2_d	cell;

// 	origin.x = data->player.pos.x; // CETTE LIGNE ma fait chier trop longtemps
// 	origin.y = data->player.pos.y; // CETTE LIGNE aussi
// 	map = origin;
// 	dir.x = ray->hit_point.x - origin.x;
// 	dir.y = ray->hit_point.y - origin.y;
// 	if (dir.x == 0)
// 		delta_dist.x = 1e30;
// 	else
// 		delta_dist.x = fabs(1.0f / dir.x);
// 	if (dir.y == 0)
// 		delta_dist.y = 1e30;
// 	else
// 		delta_dist.y = fabs(1.0f / dir.y);
// 	if (dir.x < 0)
// 	{
// 		step.x = -1; // Calcul de la direction de déplacement en X
// 		side_dist.x = (origin.x - map.x) * delta_dist.x; // Calcul de la distance à parcourir pour atteindre le prochain mur en X
// 	}
// 	else
// 	{
// 		step.x = 1;
// 		side_dist.x = (map.x + 1.0f - origin.x) * delta_dist.x;
// 	}
// 	if (dir.y < 0)
// 	{
// 		step.y = -1;
// 		side_dist.y = (origin.y - map.y) * delta_dist.y;
// 	}
// 	else
// 	{
// 		step.y = 1;
// 		side_dist.y = (map.y + 1.0f - origin.y) * delta_dist.y;
// 	}

// 	float ray_length = get_vector_d_length_squared(origin, map);

// 	while (ray_length < data->view_dst * data->view_dst)
// 	{
// 		if (side_dist.x < side_dist.y) // HIT A VERTICAL LINE
// 		{
// 			side_dist.x += delta_dist.x;
// 			map.x += step.x;
// 			ray->perp_len = (side_dist.x - delta_dist.x) * data->cell_size; // Corrected line
// 			if (step.x > 0)
// 				ray->side_hit = 2; // EAST
// 			else
// 				ray->side_hit = 3; // WEST
// 		}
// 		else // HIT A HORIZONTAL LINE
// 		{
// 			side_dist.y += delta_dist.y;
// 			map.y += step.y;
// 			ray->perp_len = (side_dist.y - delta_dist.y) * data->cell_size; // Corrected line
// 			if (step.y > 0)
// 				ray->side_hit = 0; // SOUTH
// 			else
// 				ray->side_hit = 1; // NORD
// 		}
// 		ray_length = get_vector_d_length_squared(origin, map);
// 		// Converting pixel coordinates to tab coordinates
// 		cell.x = map.x / data->cell_size;
// 		cell.y = map.y / data->cell_size;

// 		if (cell.x < 0 || cell.x >= data->win_width)
// 			continue;
// 		if (cell.y < 0 || cell.y >= data->win_height)
// 			continue;

// 		if (data->tab[cell.y][cell.x] == 1) // Is a wall
// 			return (vector_d_to_f(map));
// 	}
// 	return (vector_d_to_f(map));
// }

t_vector2_d vector_d_lerp(t_vector2_d a, t_vector2_d b, double t)
{
	t_vector2_d	v;

	v.x = a.x + (b.x - a.x) * t;
	v.y = a.y + (b.y - a.y) * t;
	return (v);
}

double get_vector_double_len(t_vector2_d origin, t_vector2_d dst)
{
	double	dx;
	double	dy;

	dx = dst.x - origin.x;
	dy = dst.y - origin.y;
	return (sqrt(dx * dx + dy * dy));
}

double	get_vector_fl_len(t_vector2_f origin, t_vector2_f dst)
{
	double	dx;
	double	dy;

	dx = dst.x - origin.x;
	dy = dst.y - origin.y;
	return (sqrt(dx * dx + dy * dy));
}

t_vector2_d	create_vector_d_from_origin(t_vector2_d origin, double angle, int len)
{
	t_vector2_d	v;

	v.x = origin.x + len * cos(angle);
	v.y = origin.y + len * sin(angle);
	return (v);
}

t_vector2_d	dda(t_data *data, t_ray* ray, int i)
{
	t_vector2_d	origin;
	t_vector2_d	map;
	t_vector2_d dir;
	t_vector2_d	side_dist;
	t_vector2_d	delta_dist;
	t_vector2_d	step;
	t_vector2_i	cell;

	(void)i;
	origin.x = (double)data->player.pos.x; // CETTE LIGNE ma fait chier trop longtemps
	origin.y = (double)data->player.pos.y; // CETTE LIGNE aussi
	map = origin;
	dir.x = ray->hit_point.x - origin.x;
	dir.y = ray->hit_point.y - origin.y;
	// if (i >= 950 && i <= 970)
	// 	printf("dir.x = %f | dir.y = %f\n", dir.x, dir.y);
	if (dir.x == 0)
		delta_dist.x = 1e30;
	else
		delta_dist.x = fabs(1.0f / dir.x);
	if (dir.y == 0)
		delta_dist.y = 1e30;
	else
		delta_dist.y = fabs(1.0f / dir.y);
	if (dir.x < 0)
	{
		step.x = -1; // Calcul de la direction de déplacement en X
		side_dist.x = (origin.x - map.x) * delta_dist.x; // Calcul de la distance à parcourir pour atteindre le prochain mur en X
	}
	else
	{
		step.x = 1;
		side_dist.x = (map.x + 1.0f - origin.x) * delta_dist.x;
		// if (i >= 950 && i <= 970)
		// 	printf("side_dist.x %d = %f\n", i, side_dist.x);
	}
	if (dir.y < 0)
	{
		step.y = -1;
		side_dist.y = (origin.y - map.y) * delta_dist.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = (map.y + 1.0f - origin.y) * delta_dist.y;
	}

	double ray_length = get_vector_double_len(origin, map);

	while (ray_length < data->view_dst * data->view_dst)
	{
		if (side_dist.x < side_dist.y) // HIT A VERTICAL LINE
		{
			side_dist.x += delta_dist.x;
			map.x += step.x;
			ray->perp_len = (side_dist.x - delta_dist.x) * data->cell_size; // Corrected line
			if (step.x > 0)
				ray->side_hit = 2; // EAST
			else
				ray->side_hit = 3; // WEST
		}
		else // HIT A HORIZONTAL LINE
		{
			side_dist.y += delta_dist.y;
			map.y += step.y;
			ray->perp_len = (side_dist.y - delta_dist.y) * data->cell_size; // Corrected line
			if (step.y > 0)
				ray->side_hit = 0; // SOUTH
			else
				ray->side_hit = 1; // NORD
		}
		ray_length = get_vector_double_len(origin, map);
		// Converting pixel coordinates to tab coordinates
		cell.x = map.x / data->cell_size;
		cell.y = map.y / data->cell_size;

		if (cell.x < 0 || cell.x >= data->win_width)
			continue;
		if (cell.y < 0 || cell.y >= data->win_height)
			continue;

		if (data->tab[cell.y][cell.x] == 1) // Is a wall
		{
			t_vector2_d impact_point;
            if (ray->side_hit == 2 || ray->side_hit == 3) // Vertical hit
                impact_point = (t_vector2_d){map.x, origin.y + (map.x - origin.x) * (dir.y / dir.x)};
            else // Horizontal hit
                impact_point = (t_vector2_d){origin.x + (map.y - origin.y) * (dir.x / dir.y), map.y};
            return impact_point;
		}
	}
	return (map);
}


// GARDER fct pour toruver les collisions qui appelle dda
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
		res = dda(data, &data->ray_array[i], i);
		// if (i >= 950 && i <= 970)
		// 		printf("map.x = %f | map.y = %f\n", res.x, res.y);
		if (res.x != -1 && res.y != -1)
		{
			data->ray_array[i].hit_point = res;
			data->ray_array[i].len = get_vector_double_len(origin, res);
		}
		else
			data->ray_array[i].len = -1;
		bresenham(data, origin, data->ray_array[i].hit_point, YELLOW); //VISU 2D
		i++;
	}
}
// GARDER fct pour creer les rayons
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

	// Définir l'origine comme la position du joueur
	origin.x = data->player.pos.x;
	origin.y = data->player.pos.y;

	// Calculer l'angle de la direction du joueur
	angle = atan2(data->player.dir.y, data->player.dir.x);

	// Calculer la position de la destination de la vue
	// view_dst_pos.x = data->player.view_dis_pos.x;
	// view_dst_pos.y = data->player.view_dis_pos.y;
	view_dst_pos.x = origin.x + data->player.dir.x * data->view_dst;
    view_dst_pos.y = origin.y + data->player.dir.y * data->view_dst;

	// draw_square(data, view_dst_pos.x, view_dst_pos.y, GREEN); // VISU 2D

	// Calculer la longueur de l'opposé pour le champ de vision
	opposite_len = tan(degree_to_radian(FOV_ANGLE / 2)) * data->view_dst;

	// Calculer les vecteurs opposés pour le champ de vision
	// opposite_vec[0] = create_vector_f_from_origin(vector_d_to_f(view_dst_pos), angle + M_PI / 2, opposite_len);
	// opposite_vec[1] = create_vector_f_from_origin(vector_d_to_f(view_dst_pos), angle - M_PI / 2, opposite_len);
	opposite_vec[0] = create_vector_d_from_origin(view_dst_pos, angle + M_PI / 2, opposite_len);
	opposite_vec[1] = create_vector_d_from_origin(view_dst_pos, angle - M_PI / 2, opposite_len);

	// draw_square(data, opposite_vec[0].x, opposite_vec[0].y, BLUE); // VISU 2D
	// draw_square(data, opposite_vec[1].x, opposite_vec[1].y, RED); 	// VISU 2D

	// Calculer l'incrément pour chaque rayon
	increment = 1.0f / (data->ray_count - 1.0f);

	// Tracer chaque rayon
	i = 0;
	while (i < data->ray_count)
	{
		vector = vector_d_lerp(opposite_vec[0], opposite_vec[1], increment * i);
		data->ray_array[i].angle = get_angle(origin, vector.x, vector.y);
		data->ray_array[i].hit_point = vector;

        // Inverser la coordonnée Y des points d'impact des rayons pour la visualisation 3D
        data->ray_array[i].hit_point.y = data->tab_height * data->cell_size - data->ray_array[i].hit_point.y;
		/* ICIIIIIIIIIIIIIIII */

		i++;
	}
}

// GARDER fct qui boucle dans la mlx_loop_hook maiss
int perform_raycasting(t_data *data)
{
	// mlx_clear_window(data->mlx, data->win);
	// printf("player pos x: %f, y: %f\n", data->player.pos.x, data->player.pos.y); // debug
	print_grind(data); // VISU 2D
	input_key(data);
	floor_and_ceiling(data); //3d
	creat_rays(data);
	calculate_collisions(data);
	rays_render(data); // 3d
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win2, data->img2, 0, 0);
	return (0);
}
