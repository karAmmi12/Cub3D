/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:21:54 by kammi             #+#    #+#             */
/*   Updated: 2024/08/28 16:24:06 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	onlywhitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
			&& str[i] != '\v' && str[i] != '\f' && str[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

void	get_map_lenght_height(t_data *data)
{
	int	i;
	int	j;
	int	height;

	i = 0;
	height = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
			j++;
		if (j > data->fileinfo.map_lenght)
			data->fileinfo.map_lenght = j;
		if (data->map[i][0] != '\n' && !onlywhitespace(data->map[i]))
			height++;
		i++;
	}
	data->fileinfo.map_height = height;
}

char	**copy_map(char **map, t_data *data)
{
	char	**copy_map;
	int		i;
	int		j;
	int		len;

	len = ft_tablen(map);
	if (len == 0)
		exit_read(data, "Error :\n Empty map\n");
	copy_map = malloc(sizeof(char *) * (len + 1));
	if (copy_map == NULL)
		exit_read(data, "Error: Malloc error\n");
	i = 0;
	while (i < len)
	{
		copy_map[i] = malloc(sizeof(char) * (ft_strlen(map[i]) + 1));
		if (copy_map[i] == NULL)
			exit_read(data, "Error: Malloc error\n");
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