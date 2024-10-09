/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:40:30 by apintus           #+#    #+#             */
/*   Updated: 2024/10/09 13:05:23 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mouse_press(int button, int x, int y, t_data *data)
{
	printf("button: %d, x: %d, y: %d\n", button, x, y);
	data->mouse_button = button;
	set_grid_cell(data, x, y);
	return (0);
}

int	mouse_release(int button, int x, int y, t_data *data)
{
	printf("button: %d, x: %d, y: %d\n", button, x, y);
	data->mouse_button = 0;
	return (0);
}

// int	mouse_move(int x, int y, t_data *data)
// {
// 	printf("x: %d, y: %d\n", x, y);
// 	data->mouse_x = x;
// 	data->mouse_y = y;
// 	if (data->mouse_button != 0)
// 	{
// 		set_grid_cell(data, x, y);
// 	}
// 	return (0);
// }

int	key_press(int keycode, t_data *data)
{
	printf("keycode: %d\n", keycode);
	if (keycode < 200)
		data->keyboard[keycode] = 1;
	if (keycode == 65307)
		close_game(data);
	if (keycode == KEY_LEFT)
		data->keyboard[201] = 1;
	if (keycode == KEY_RIGHT)
		data->keyboard[202] = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode < 200)
		data->keyboard[keycode] = 0;
	if (keycode == KEY_LEFT)
		data->keyboard[201] = 0;
	if (keycode == KEY_RIGHT)
		data->keyboard[202] = 0;
	return (0);
}
