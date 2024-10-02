/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:15:09 by apintus           #+#    #+#             */
/*   Updated: 2024/10/02 11:50:10 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// GARDER mais modifier pour que ce soit les fleches
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
// GARDER mais modifier pour que ce soit les fleches
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

// GARDER fct pour verifier si il y a une collision
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

// GARDER fct pour gerer les touches | AJOUTER LES FLECHES
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