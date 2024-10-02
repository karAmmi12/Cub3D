/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:22:37 by apintus           #+#    #+#             */
/*   Updated: 2024/10/02 11:51:17 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// GARDER fct pour avancer
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
// GARDER fct pour reculer
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
/**************************** */
/*CREER LES MOVE LEFT ET RIGHT*/
/**************************** */
