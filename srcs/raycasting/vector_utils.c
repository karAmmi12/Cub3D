/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:11:17 by apintus           #+#    #+#             */
/*   Updated: 2024/10/01 15:17:29 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//GARDER fct pour calculer l angle entre 2 points
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

// GARDER fct pour convertir les degres en radian
double	degree_to_radian(double degree)
{
	return (degree * PI / 180);
}
// GARDER fct pour creer un vecteur F a partir d un angle
t_vector2_f	create_vector_f_from_origin(t_vector2_f origin, double angle, int len)
{
	t_vector2_f	v;

	v.x = origin.x + len * cos(angle);
	v.y = origin.y + len * sin(angle);
	return (v);
}
// GARDER fct pour passer de vector double a vector float
t_vector2_f	vector_d_to_f(t_vector2_d v)
{
	t_vector2_f	f;

	f.x = v.x;
	f.y = v.y;
	return (f);
}
// GARDER fct pour faire une interpolation lineaire (trouver un point entre 2 points)
t_vector2_f	vector_f_lerp(t_vector2_f a, t_vector2_f b, double t)
{
	t_vector2_f	v;

	v.x = a.x + (b.x - a.x) * t;
	v.y = a.y + (b.y - a.y) * t;
	return (v);
}

// GARDER fct calculer la distance entre 2 points
float	get_vector_d_length_squared(t_vector2_d a, t_vector2_d b)
{
	float	dx;
	float	dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	return (dx * dx + dy * dy);
}

// GARDER fct pour calculer la longueur d un vecteur
double	get_vector_f_len(t_vector2_d origin, t_vector2_f dst)
{
	double	dx;
	double	dy;

	dx = dst.x - origin.x;
	dy = dst.y - origin.y;
	return (sqrt(dx * dx + dy * dy));
}
