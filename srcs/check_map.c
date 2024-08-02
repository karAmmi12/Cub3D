/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:52:50 by apintus           #+#    #+#             */
/*   Updated: 2024/08/02 13:44:35 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_map_lenght_height(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
			j++;
		if (j > data->fileinfo.map_lenght)
			data->fileinfo.map_lenght = j;
		i++;
	}
	data->fileinfo.map_height = i;
	printf("%d\n", data->fileinfo.map_lenght);
	printf("%d\n", data->fileinfo.map_height);
}

char	**copy_map(char **map, t_data *data)
{
	char	**copy_map;
	int	i;
	int	j;

	copy_map = malloc(sizeof(char *) * (ft_tablen(map) + 1));
	i = 0;
	while (i < ft_tablen(map))
	{
		copy_map[i] = malloc(sizeof(char) * (ft_strlen(map[i]) + 1));
		j = 0;
		while (map[i][j])
		{
			copy_map[i][j] = map[i][j];
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
			{
				data->pos_x = j;
				data->pos_y = i;
			}
			j++;
		}
		copy_map[i][j] = '\0';
		i++;
	}
	copy_map[i] = NULL;
	return (copy_map);
}

int	check_flood_fill(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->fileinfo.copy_map[i])
	{
		j = 0;
		while (data->fileinfo.copy_map[i][j])
		{
			if (data->fileinfo.copy_map[i][j] != 'X' && data->fileinfo.copy_map[i][j] != '1'
				&& data->fileinfo.copy_map[i][j] != ' ')
				{
					printf("%c\n", data->fileinfo.copy_map[i][j]);
					exit_read(data, "Error: Map not closed\n");
				}
			j++;
		}
		i++;
	}
	return (0);
}

void	flood_fill(t_data *data, int x, int y, char **map)
{
	if (map[y][x] == '1' || map[y][x] == 'X')
		return ;
	map[y][x] = 'X';
	flood_fill(data, x + 1, y, map);
	flood_fill(data, x - 1, y, map);
	flood_fill(data, x, y + 1, map);
	flood_fill(data, x, y - 1, map);
	return ;
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int	is_map_closed(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	
}

int	check_map(t_data *data)
{
	data->map = copy_map(data->fileinfo.copy_map, data);
	get_map_lenght_height(data);
	if (is_map_closed(data, data->map))
		printf("OK map closed\n");
	else
		printf("KO map not closed\n");
	// flood_fill(data, data->pos_x, data->pos_y, data->fileinfo.copy_map);
	// print_map(data->fileinfo.copy_map);
	// check_flood_fill(data);
	// pas faire flood fill mais checker la premiere et derniere ligne en prenant en compte les esapces
	return (0);
}
