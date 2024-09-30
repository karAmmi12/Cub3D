/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:43:00 by apintus           #+#    #+#             */
/*   Updated: 2024/09/30 15:24:39 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= data->win_width || y >= data->win_height)
		return ;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	init_tab(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	data->tab_height = 15;
	data->tab_width = 20;
	data->tab = malloc(sizeof(int *) * data->tab_height);
	if (data->tab == NULL)
		return (1);
	while (y < data->tab_height)
	{
		data->tab[y] = malloc(sizeof(int) * data->tab_width);
		if (data->tab[y] == NULL)
			return (1);
		while (x < data->tab_width)
		{
			if (x == 0 || y == 0 || x == data->tab_width - 1 || y == data->tab_height - 1)
				data->tab[y][x] = 1;
			else
				data->tab[y][x] = 0;
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

void	draw_square(t_data *data, int x, int y, int color)
{
    for (int i = -2; i <= 2; i++)
    {
        for (int j = -2; j <= 2; j++)
        {
            my_mlx_pixel_put(data, x + i, y + j, color);
        }
    }
}

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

void	print_grind(t_data *data)
{
	int	x;
	int	y;
	t_vector2_d top_left;
	t_vector2_d bottom_right;

	x = 0;
	y = 0;
	while (y < data->tab_height)
	{
		while (x < data->tab_width)
		{
			top_left.x = x * data->cell_size;
			top_left.y = y * data->cell_size;
			bottom_right.x = top_left.x + data->cell_size;
			bottom_right.y = top_left.y + data->cell_size;
			if (data->tab[y][x] == 1) // VISU 2d
				draw_rect_color(data, top_left, bottom_right, PINK);
			else
				draw_rect_color(data, top_left, bottom_right, BLACK);
			x++;
		}
		x = 0;
		y++;
	}
}

void	set_grid_cell(t_data *data, int x, int y)
{
	t_vector2_d	tab_pos;

	tab_pos.x = x / data->cell_size;
	tab_pos.y = y / data->cell_size;
	if (x < 0 || y < 0 || tab_pos.x >= data->tab_width || tab_pos.y >= data->tab_height)
		return ;
	if (data->mouse_button == LMB)
		data->tab[tab_pos.y][tab_pos.x] = 1;
	else if (data->mouse_button == RMB)
		data->tab[tab_pos.y][tab_pos.x] = 0;
}

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        my_mlx_pixel_put(data, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

double	get_angle(t_vector2_d origin, int x, int y)
{
	double	angle;
	double	dx;
	double	dy;

	dx = x - origin.x;
	dy = y - origin.y;
	angle = atan2(dy, dx);
	return (angle);
}

t_vector2_d	create_vector_d_from_origin(t_vector2_d origin, double angle, int len)
{
	t_vector2_d	v;

	v.x = origin.x + len * cos(angle);
	v.y = origin.y + len * sin(angle);
	return (v);
}

double	degree_to_radian(double degree)
{
	return (degree * PI / 180);
}
t_vector2_f	create_vector_f_from_origin(t_vector2_f origin, double angle, int len)
{
	t_vector2_f	v;

	v.x = origin.x + len * cos(angle);
	v.y = origin.y + len * sin(angle);
	return (v);
}

t_vector2_f	vector_d_to_f(t_vector2_d v)
{
	t_vector2_f	f;

	f.x = v.x;
	f.y = v.y;
	return (f);
}

t_vector2_f	vector_f_lerp(t_vector2_f a, t_vector2_f b, double t)
{
	t_vector2_f	v;

	v.x = a.x + (b.x - a.x) * t;
	v.y = a.y + (b.y - a.y) * t;
	return (v);
}

// WTFFF SUPER MULTI RAYON JAUUU
void	bresenham(t_data *data, t_vector2_d origin, t_vector2_f dst, int color)
{
    int	dx;
    int	dy;
    int	sx;
    int	sy;
    int	err;
    int	e2;
    int	x;
    int	y;

    dx = abs((int)dst.x - (int)origin.x);
    dy = abs((int)dst.y - (int)origin.y);
    sx = (origin.x < dst.x) ? 1 : -1;
    sy = (origin.y < dst.y) ? 1 : -1;
    err = dx - dy;
    x = (int)origin.x;
    y = (int)origin.y;
    while (1)
    {
        // Assurez-vous que les coordonnées sont dans les limites de l'écran
        if (x >= 0 && x < data->win_width && y >= 0 && y < data->win_height)
            my_mlx_pixel_put(data, x, y, color);
        if (x == (int)dst.x && y == (int)dst.y)
            break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y += sy;
        }
    }
}

float	get_vector_d_length_squared(t_vector2_d a, t_vector2_d b)
{
	float	dx;
	float	dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	return (dx * dx + dy * dy);
}

t_vector2_f	dda(t_data *data, t_ray* ray)
{
	t_vector2_d	origin;
	t_vector2_d	map;
	t_vector2_f dir;
	t_vector2_f	side_dist;
	t_vector2_f	delta_dist;
	t_vector2_f	step;
	t_vector2_d	cell;

	origin.x = data->player.pos.x; // CETTE LIGNE EST A CHANGER !!!!!!!!!
	origin.y = data->player.pos.y; // CETTE LIGNE EST A CHANGER !!!!!!!!!!!!!!
	map = origin;
	dir.x = ray->hit_point.x - origin.x;
	dir.y = ray->hit_point.y - origin.y;
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

	// while (1)
	// {
	// 	if (side_dist.x < side_dist.y)
	// 	{
	// 		side_dist.x += delta_dist.x;
	// 		map.x += step.x;
	// 		ray->side_hit = 0; // mur vertical
	// 	}
	// 	else
	// 	{
	// 		side_dist.y += delta_dist.y;
	// 		map.y += step.y;
	// 		ray->side_hit = 1; // mur horizontal
	// 	}
	// 	// convert map to cell
	// 	cell.x = map.x / data->cell_size;
	// 	cell.y = map.y / data->cell_size;

	// 	if (data->tab[cell.y][cell.x] == 1)
	// 	{
	// 		ray->hit_point = vector_d_to_f(map);
	// 		ray->cell = cell;
	// 		if (ray->side_hit == 0)
	// 			ray->len = (map.x - origin.x + (1 - step.x) / 2) / dir.x;
	// 		else
	// 			ray->len = (map.y - origin.y + (1 - step.y) / 2) / dir.y;
	// 		return (ray->hit_point);
	// 	}
	// }
	float ray_length = get_vector_d_length_squared(origin, map);

	while (ray_length < data->view_dst * data->view_dst)
	{
	  if (side_dist.x < side_dist.y) // HIT A VERTICAL LINE
	  {
	    side_dist.x += delta_dist.x;
	    map.x += step.x;
		ray->perp_len = (side_dist.y - delta_dist.y) * data->cell_size;// FIShing eye effect
		if (step.x > 0)
			ray->side_hit = 2; // EAST
		else
			ray->side_hit = 3; // WEST
	  }
	  else // HIT A HORIZONTAL LINE
	  {
	    side_dist.y += delta_dist.y;
	    map.y += step.y;
		ray->perp_len = (side_dist.x - delta_dist.x) * data->cell_size;// FIShing eye effect
		if (step.y > 0)
			ray->side_hit = 1; // SOUTH
		else
			ray->side_hit = 0; // NORTH
	  }

	  ray_length = get_vector_d_length_squared(origin, map);

	  // Converting pixel coordinates to tab coordinates
	  cell.x = map.x / data->cell_size;
	  cell.y = map.y / data->cell_size;

	  if (cell.x < 0 || cell.x >= data->win_width)
	    continue;
	  if (cell.y < 0 || cell.y >= data->win_height)
	    continue;

	  if (data->tab[cell.y][cell.x] == 1) // Is a wall
	  {
	    return (vector_d_to_f(map));
	  }
	}
	return (vector_d_to_f(map));
}

// void	creat_rays(t_data *data)
// {
// 	t_vector2_d	origin;
// 	double		angle;
// 	t_vector2_d	view_dst_pos;
// 	int			opposite_len;
// 	t_vector2_f	opposite_vec[2];
// 	double		increment;
// 	int			i;
// 	t_vector2_f	vector;

// 	origin.x = data->tab_width * data->cell_size / 2;
// 	origin.y = data->tab_height * data->cell_size / 2;
// 	angle = get_angle(origin, data->player.dir.x, data->player.dir.y);
// 	view_dst_pos = create_vector_d_from_origin(origin, angle, data->view_dst);
// 	draw_square(data, view_dst_pos.x, view_dst_pos.y, GREEN);
// 	opposite_len = tan(degree_to_radian(FOV_ANGLE / 2)) * data->view_dst;
// 	opposite_vec[0] = create_vector_f_from_origin(vector_d_to_f(view_dst_pos), angle + PI / 2, opposite_len);
// 	opposite_vec[1] = create_vector_f_from_origin(vector_d_to_f(view_dst_pos), angle - PI / 2, opposite_len);
// 	draw_square(data, opposite_vec[0].x, opposite_vec[0].y, BLUE);
// 	draw_square(data, opposite_vec[1].x, opposite_vec[1].y, RED);
// 	increment = 1.0f / (data->ray_count - 1.0f);
// 	i = 0;
// 	while (i < data->ray_count)
// 	{
// 		vector = vector_f_lerp(opposite_vec[0], opposite_vec[1], increment * i);
// 		// bresenham(data, origin, vector, YELLOW);
// 		data->ray_array[i].angle = get_angle(origin, vector.x, vector.y);
// 		data->ray_array[i].hit_point = vector;
// 		i++;
// 	}
//     i = 0;
//     while (i < data->ray_count)
//     {
//         dda(data, &data->ray_array[i]);
// 		bresenham(data, origin, data->ray_array[i].hit_point, YELLOW);
//         i++;
//     }
// }

// int perform_raycasting(t_data *data)
// {
// 	int			i;
// 	t_vector2_f	hit;
// 	int			center_x;
// 	int			center_y;

// 	i = 0;
// 	center_x = data->tab_width * data->cell_size / 2;
// 	center_y = data->tab_height * data->cell_size / 2;

// 	mlx_clear_window(data->mlx, data->win);
// 	print_grind(data);

// 	data->ray_array[i].hit_point.x = data->mouse_x;
// 	data->ray_array[i].hit_point.y = data->mouse_y;

// 	hit = dda(data, &data->ray_array[i]);
// 	draw_line(data, center_x, center_y, hit.x, hit.y, WHITE);
// 	draw_square(data, hit.x, hit.y, RED);
// 	creat_rays(data);
// 	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
// 	return (0);
// }

int	rotate_left(t_data *data)
{
	double	rot_speed;
	double	old_dir_x;

	rot_speed = 0.1;
	old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(-rot_speed) - data->player.dir.y * sin(-rot_speed);
	data->player.dir.y = old_dir_x * sin(-rot_speed) + data->player.dir.y * cos(-rot_speed);
	return (0);
}

int	rotate_right(t_data *data)
{
	double	rot_speed;
	double	old_dir_x;

	rot_speed = 0.1;
	old_dir_x = data->player.dir.x;
	data->player.dir.x = data->player.dir.x * cos(rot_speed) - data->player.dir.y * sin(rot_speed);
	data->player.dir.y = old_dir_x * sin(rot_speed) + data->player.dir.y * cos(rot_speed);
	return (0);
}
int is_colliding(t_data *data, float x, float y)
{
	t_vector2_d	cell;

	cell.x = x / data->cell_size;
	cell.y = y / data->cell_size;
	if (cell.x < 0 || cell.x >= data->tab_width)
		return (0);
	if (cell.y < 0 || cell.y >= data->tab_height)
		return (0);
	if (data->tab[(int)cell.y][(int)cell.x] == 1)
		return (1);
	return (0);
}

int	move_forward(t_data *data)
{
	t_vector2_f *p_pos;
	int	move_speed;

	p_pos = &data->player.pos;
	move_speed = 10;
	if (!is_colliding(data, p_pos->x + data->player.dir.x * move_speed, p_pos->y))
		p_pos->x += data->player.dir.x * move_speed;
	if (!is_colliding(data, p_pos->x, p_pos->y + data->player.dir.y * move_speed))
		p_pos->y += data->player.dir.y * move_speed;
	return (0);
}


int	move_backward(t_data *data)
{
	t_vector2_f *p_pos;
	int	move_speed;

	p_pos = &data->player.pos;
	move_speed = 10;
	if (!is_colliding(data, p_pos->x - data->player.dir.x * move_speed, p_pos->y))
		p_pos->x -= data->player.dir.x * move_speed;
	if (!is_colliding(data, p_pos->x, p_pos->y - data->player.dir.y * move_speed))
		p_pos->y -= data->player.dir.y * move_speed;
	return (0);
}

int	input_key(t_data *data)
{
	if (data->keyboard[KEY_D])
		rotate_left(data); // inverser
	if (data->keyboard[KEY_A])
		rotate_right(data); // inverser
	if (data->keyboard[KEY_W])
		move_forward(data);
	if (data->keyboard[KEY_S])
		move_backward(data);
	data->player.view_dis_pos.x = data->player.dir.x * data->view_dst + data->player.pos.x;
	data->player.view_dis_pos.y = data->player.dir.y * data->view_dst + data->player.pos.y;
	// printf("view_dis_pos x: %f, y: %f\n", data->player.view_dis_pos.x, data->player.view_dis_pos.y);
	return (0);
}

// int perform_raycasting(t_data *data)
// {
//     int i;
//     t_vector2_f hit;
//     int center_x;
//     int center_y;
//     float angle_step;
//     float start_angle;
//     float mouse_angle;

//     // center_x = data->tab_width * data->cell_size / 2;
//     // center_y = data->tab_height * data->cell_size / 2;
// 	center_x = data->player.pos.x;
// 	center_y = data->player.pos.y;

//     mlx_clear_window(data->mlx, data->win);
//     print_grind(data);

//     // Calculer l'angle de la souris par rapport à la position du joueur
//     mouse_angle = atan2f(data->mouse_y - center_y, data->mouse_x - center_x);

//     // Calculer l'angle de départ pour le champ de vision
//     start_angle = mouse_angle - degree_to_radian(FOV_ANGLE / 2.0f);

//     // Calculer l'incrément d'angle pour chaque rayon
//     angle_step = degree_to_radian(FOV_ANGLE) / data->ray_count;

//     // Tracer chaque rayon
//     for (i = 0; i < data->ray_count; i++) {
//         data->ray_angles[i] = start_angle + i * angle_step;
//         data->ray_array[i].hit_point.x = center_x + cosf(data->ray_angles[i]) * data->view_dst;
//         data->ray_array[i].hit_point.y = center_y + sinf(data->ray_angles[i]) * data->view_dst;

//         hit = dda(data, &data->ray_array[i]);
//         bresenham(data, (t_vector2_d){center_x, center_y}, hit, WHITE);
//         draw_square(data, hit.x, hit.y, RED);
//     }

//     mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
//     return (0);
// }

/*********/
double	get_vector_f_len(t_vector2_d origin, t_vector2_f dst)
{
	double	dx;
	double	dy;

	dx = dst.x - origin.x;
	dy = dst.y - origin.y;
	return (sqrt(dx * dx + dy * dy));
}

void	calculate_collisions(t_data *data)
{
	t_vector2_d	origin;
	t_vector2_f	res;
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
			data->ray_array[i].len = get_vector_f_len(origin, res);
		}
		else
			data->ray_array[i].len = -1;
		// bresenham(data, origin, data->ray_array[i].hit_point, YELLOW); //VISU 2D
		i++;
	}
}

void creat_rays(t_data *data)
{
    t_vector2_d origin;
    double angle;
    t_vector2_d view_dst_pos;
    int opposite_len;
    t_vector2_f opposite_vec[2];
    double increment;
    int i;
    t_vector2_f vector;

    // Définir l'origine comme la position du joueur
    origin.x = data->player.pos.x;
    origin.y = data->player.pos.y;

    // Calculer l'angle de la direction du joueur
    angle = atan2(data->player.dir.y, data->player.dir.x);

    // Calculer la position de la destination de la vue
    // view_dst_pos = create_vector_d_from_origin(origin, angle, data->view_dst); ICICICI
	view_dst_pos.x = data->player.view_dis_pos.x;
	view_dst_pos.y = data->player.view_dis_pos.y;

    // draw_square(data, view_dst_pos.x, view_dst_pos.y, GREEN); // VISU 2D

    // Calculer la longueur de l'opposé pour le champ de vision
    opposite_len = tan(degree_to_radian(FOV_ANGLE / 2)) * data->view_dst;

    // Calculer les vecteurs opposés pour le champ de vision
    opposite_vec[0] = create_vector_f_from_origin(vector_d_to_f(view_dst_pos), angle + M_PI / 2, opposite_len);
    opposite_vec[1] = create_vector_f_from_origin(vector_d_to_f(view_dst_pos), angle - M_PI / 2, opposite_len);
    // draw_square(data, opposite_vec[0].x, opposite_vec[0].y, BLUE); // VISU 2D
    // draw_square(data, opposite_vec[1].x, opposite_vec[1].y, RED); 	// VISU 2D

    // Calculer l'incrément pour chaque rayon
    increment = 1.0f / (data->ray_count - 1.0f);

    // Tracer chaque rayon
    i = 0;
    while (i < data->ray_count)
    {
        vector = vector_f_lerp(opposite_vec[0], opposite_vec[1], increment * i);
		// bresenham(data, origin, vector, YELLOW);
		data->ray_array[i].angle = get_angle(origin, vector.x, vector.y);
		data->ray_array[i].hit_point = vector;
        i++;
    }
    // // Utiliser l'algorithme de DDA pour trouver les points d'impact
    // i = 0;
    // while (i < data->ray_count)
    // {
    //     dda(data, &data->ray_array[i]);
    //     bresenham(data, origin, data->ray_array[i].hit_point, YELLOW);
    //     i++;
    // }
}

void	floor_and_celling(t_data *data)
{
	int	floor_color;
	int	ceiling_color;
	int	x;
	int	y;

	// floor_color = data->fileinfo.floor[0] << 16 | data->fileinfo.floor[1] << 8 | data->fileinfo.floor[2];
	// ceiling_color = data->fileinfo.celling[0] << 16 | data->fileinfo.celling[1] << 8 | data->fileinfo.celling[2];
	floor_color = PURPLE;
	ceiling_color = GREY;
	x = 0;
	y = 0;
	while (y < data->win_height / 2)
	{
		while (x < data->win_width)
		{
			my_mlx_pixel_put(data, x, y, floor_color);
			x++;
		}
		x = 0;
		y++;
	}
	y = data->win_height / 2;
	while (y < data->win_height)
	{
		while (x < data->win_width)
		{
			my_mlx_pixel_put(data, x, y, ceiling_color);
			x++;
		}
		x = 0;
		y++;
	}
}

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

int perform_raycasting(t_data *data)
{
    mlx_clear_window(data->mlx, data->win);
    // print_grind(data); // VISU 2D
	input_key(data);
	// draw_square(data, data->player.pos.x, data->player.pos.y, PURPLE); // VISU 2D
	floor_and_ceiling(data);
    creat_rays(data);
	calculate_collisions(data);
	rays_render(data); // 3d
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return (0);
}
