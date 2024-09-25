/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:52:18 by apintus           #+#    #+#             */
/*   Updated: 2024/09/23 16:16:28 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static	int get_max_line_length(char **map)
{
	int	max_len;
	int	i;
	int	len;

	i = 0;
	max_len = 0;
	while (map[i])
	{
		len = strlen(map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}

// Fonction pour rendre la carte rectangulaire
void	make_map_rectangular(t_data *data)
{
	int		max_len;
	int		i;
	int		j;
	int		len;
	char	*new_line;

	i = 0;
	max_len = get_max_line_length(data->fileinfo.copy_map);
	while (data->fileinfo.copy_map[i])
	{
		len = strlen(data->fileinfo.copy_map[i]);
		if (len < max_len)
		{
			new_line = malloc(max_len + 1);
			if (!new_line)
				return; // Gérer l'erreur de malloc
			ft_strcpy(new_line, data->fileinfo.copy_map[i]);
			ft_memset(new_line + len, '1', max_len - len);
			new_line[max_len] = '\0';
			free(data->fileinfo.copy_map[i]);
			data->fileinfo.copy_map[i] = new_line;
		}
		// Remplacer tous les espaces par des '1'
		j = 0;
		while (j < max_len)
		{
			if (data->fileinfo.copy_map[i][j] == ' ')
				data->fileinfo.copy_map[i][j] = '1';
			j++;
		}
		i++;
	}
}
void	get_map_Width_Height(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->mapWidth = 0;
	data->mapHeight = 0;
	while (data->fileinfo.copy_map[i][j])
	{
		data->mapWidth++;
		j++;
	}
	while (data->fileinfo.copy_map[i])
	{
		data->mapHeight++;
		i++;
	}
}

// Fonction d'initialisation de la carte
void	init_map(t_data *data)
{
	make_map_rectangular(data);
	get_map_Width_Height(data);
	print_map(data->fileinfo.copy_map); //visu
	printf("pos x = %f\n", data->pos_x); //visu
	printf("pos y = %f\n", data->pos_y); //visu
	printf("map width = %d\n", data->mapWidth); //visu
	printf("map height = %d\n", data->mapHeight); //visu
	// Autres initialisations si nécessaire
}