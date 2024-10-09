/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:38:23 by apintus           #+#    #+#             */
/*   Updated: 2024/10/09 13:29:33 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_north_texture(char *str, int *i, t_data *data)
{
	*i += 2;
	while (is_whitespace(str[*i]))
		(*i)++;
	if (data->info.n_flag == 1)
		exit_read(data, "Error :\nTexture north in double\n", 0);
	data->info.north = ft_strdup(&str[*i]);
	data->info.n_flag = 1;
}

void	get_south_texture(char *str, int *i, t_data *data)
{
	*i += 2;
	while (is_whitespace(str[*i]))
		(*i)++;
	if (data->info.s_flag == 1)
		exit_read(data, "Error :\nTexture south in double\n", 0);
	data->info.south = ft_strdup(&str[*i]);
	data->info.s_flag = 1;
}

void	get_west_texture(char *str, int *i, t_data *data)
{
	*i += 2;
	while (is_whitespace(str[*i]))
		(*i)++;
	if (data->info.w_flag == 1)
		exit_read(data, "Error :\nTexture west in double\n", 0);
	data->info.west = ft_strdup(&str[*i]);
	data->info.w_flag = 1;
}

void	get_east_texture(char *str, int *i, t_data *data)
{
	*i += 2;
	while (is_whitespace(str[*i]))
		(*i)++;
	if (data->info.e_flag == 1)
		exit_read(data, "Error :\nTexture east in double\n", 0);
	data->info.east = ft_strdup(&str[*i]);
	data->info.e_flag = 1;
}

void	get_texture(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == 'N' && str[i + 1] == 'O')
		get_north_texture(str, &i, data);
	else if (str[i] == 'S' && str[i + 1] == 'O')
		get_south_texture(str, &i, data);
	else if (str[i] == 'W' && str[i + 1] == 'E')
		get_west_texture(str, &i, data);
	else if (str[i] == 'E' && str[i + 1] == 'A')
		get_east_texture(str, &i, data);
}
