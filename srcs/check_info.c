/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:46:56 by apintus           #+#    #+#             */
/*   Updated: 2024/08/22 17:34:41 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	second_check(t_data *data)
{
	if (check_ext_xpm(data->fileinfo.north) == 1)
		exit_read(data, "Error\nNorth texture is not a xpm file\n");
	if (check_ext_xpm(data->fileinfo.south) == 1)
		exit_read(data, "Error\nSouth texture is not a xpm file\n");
	if (check_ext_xpm(data->fileinfo.east) == 1)
		exit_read(data, "Error\nEast texture is not a xpm file\n");
	if (check_ext_xpm(data->fileinfo.west) == 1)
		exit_read(data, "Error\nWest texture is not a xpm file\n");
	if (data->fileinfo.floor[0] < 0 || data->fileinfo.floor[0] > 255 ||
		data->fileinfo.floor[1] < 0 || data->fileinfo.floor[1] > 255 ||
		data->fileinfo.floor[2] < 0 || data->fileinfo.floor[2] > 255)
		exit_read(data, "Error\nFloor color is not valid\n");
	if (data->fileinfo.celling[0] < 0 || data->fileinfo.celling[0] > 255 ||
		data->fileinfo.celling[1] < 0 || data->fileinfo.celling[1] > 255 ||
		data->fileinfo.celling[2] < 0 || data->fileinfo.celling[2] > 255)
		exit_read(data, "Error\nCelling color is not valid\n");
	printf("OK second check\n"); // a supp
	return (0);
}

int	check_before_map(t_data *data)
{
	if (data->fileinfo.north == NULL || data->fileinfo.south == NULL ||
		data->fileinfo.east == NULL || data->fileinfo.west == NULL)
		exit_read(data, "Error\nMap mal place\n");
	if (data->fileinfo.floor[0] == -1 || data->fileinfo.floor[1] == -1 ||
		data->fileinfo.floor[2] == -1 || data->fileinfo.celling[0] == -1 ||
		data->fileinfo.celling[1] == -1 || data->fileinfo.celling[2] == -1)
		exit_read(data, "Error\nMap mal place\n");
	printf("OK check before map\n"); // a supp
	second_check(data);
	return (0);
}
