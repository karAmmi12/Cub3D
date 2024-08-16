/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:52:50 by apintus           #+#    #+#             */
/*   Updated: 2024/08/16 15:25:02 by apintus          ###   ########.fr       */
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
	// printf("%d\n", data->fileinfo.map_lenght);
	// printf("%d\n", data->fileinfo.map_height);
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
/***********************flood fill***************************** */
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
/************ancien check ******* */
int	check_ligne(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	(void)data;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			while (map[i][j] == ' ')
				j++;
			if (map[i][j] != '1')
				return (printf("carac = %c\nLine = %d %d\n", map[i][j], i, j),0);
			while (map[i][j] != '\0')
			{
				while (map[i][j] != ' ' && map[i][j] != '\0')
					j++;
				if (map[i][j] == ' ' && map[i][j - 1] == '1')
					while (map[i][j] == ' ')
						j++;
				else if (map[i][j] != '\0')
					return (printf("carac = %c\nline = %d %d\n", map[i][j], i, j),0);
				if (map[i][j] != '1' && map[i][j] != '\0')
					return (printf("Carac = %c\nline = %d %d\n", map[i][j], i, j),0);
				if (map[i][j] == '\0' && map[i][j - 1] != '1')
					return (printf("CaraC = %c\nline = %d %d\n", map[i][j], i, j),0);
				j++;
			}
		}
		i++;
	}
	return (1);
}

int check_colonne(t_data *data, char **map)
{
	int i;
	int j;
	int max_col;
	int height;

	j = 0;
	max_col = data->fileinfo.map_lenght;
	height = data->fileinfo.map_height - 1;
	while (j < max_col)
	{
		i = 0;
		while (i < height)
		{
			while (i < height && map[i][j] == ' ')
				i++;
			if (i < height && map[i][j] != '1')
				return (printf("carac = %c\nolonne = %d %d\n", map[i][j], i, j), 0);
			while (i < height && map[i][j])
			{
				while (i < height && map[i][j] != ' ' && map[i][j])
					i++;
				if (i < height && map[i][j] == ' ' && map[i - 1][j] == '1')
					while (i < height && map[i][j] == ' ')
						i++;
				else if (i < height && map[i][j] != '1' && map[i][j])
					return (printf("carac = %c\nColonne = %d %d\n", map[i][j], i, j), 0);
				if (i < height && map[i][j] && map[i - 1][j] != '1')
					return (printf("CaraC = %c\nColonne = %d %d\n", map[i][j], i, j), 0);
				i++;
			}
		}
		j++;
	}
	return (1);
}

int	is_map_closed(t_data *data, char **map)
{
	if (check_colonne(data, map) && check_ligne(data, map))
		return (1);
	return (0);
}
/******************************* */

/* int validate_map(char **map, int height)
{
	int	i;
	int	j;
	int	k;
	int	len_curr;
	int	len_top;
	int	len_bottom;

	i = 0;
	while (i < height)
	{
		len_curr = strlen(map[i]); // Longueur de la ligne actuelle
		if (i > 0)
			len_top = strlen(map[i - 1]); // Longueur de la ligne précédente
		else
			len_top = 0;

		if (i < height - 1)
			len_bottom = strlen(map[i + 1]); // Longueur de la ligne suivante
		else
			len_bottom = 0;

		// Ignorer les espaces en début de ligne
		j = 0;
		while (j < len_curr && map[i][j] == ' ')
			j++;

		// Vérifier la première et la dernière ligne
		if (i == 0 || i == height - 1)
		{
			k = j;
			while (k < len_curr)
			{
				if (map[i][k] != '1' && map[i][k] != ' ')
					return (0); // La carte n'est pas valide
				k++;
			}
		}
		else
		{
			// Vérifier que le premier et le dernier caractère sont des '1'
			if (map[i][j] != '1' || map[i][len_curr - 1] != '1')
				return (0); // La carte n'est pas valide

			// Vérifier les caractères adjacents aux espaces
			int k = j;
			while (k < len_curr)
			{
				if (map[i][k] == ' ' && ((k > 0 && map[i][k - 1] != '1' && map[i][k - 1] != ' ') ||
										 (k < len_curr - 1 && map[i][k + 1] != '1' && map[i][k + 1] != ' ')))
					return (0); // La carte n'est pas valide

				// Vérifier les règles de longueur de ligne
				if ((len_curr > len_top && k >= len_top && map[i][k] != '1') ||
					(len_curr > len_bottom && k >= len_bottom && map[i][k] != '1'))
					return (0); // La carte n'est pas valide
				k++;
			}
		}
		i++;
	}
	return (1); // La carte est valide
} */
/*******fonction decouper0 ******************/

void initialize_lengths(char **map, int height, t_map_vars *vars)
{
	vars->len_curr = strlen(map[vars->i]); // Longueur de la ligne actuelle
	if (vars->i > 0)
		vars->len_top = strlen(map[vars->i - 1]); // Longueur de la ligne précédente
	else
		vars->len_top = 0;

	if (vars->i < height - 1)
		vars->len_bottom = strlen(map[vars->i + 1]); // Longueur de la ligne suivante
	else
		vars->len_bottom = 0;
}

int validate_first_last_line(char **map, t_map_vars *vars)
{
	vars->k = vars->j;
	while (vars->k < vars->len_curr)
	{
		if (map[vars->i][vars->k] != '1' && map[vars->i][vars->k] != ' ')
			return (0); // La carte n'est pas valide
		vars->k++;
	}
	return (1);
}

int validate_middle_line(char **map, t_map_vars *vars)
{
	// Vérifier que le premier et le dernier caractère sont des '1'
	if (map[vars->i][vars->j] != '1' || map[vars->i][vars->len_curr - 1] != '1')
		return (0); // La carte n'est pas valide

	// Vérifier les caractères adjacents aux espaces
	vars->k = vars->j;
	while (vars->k < vars->len_curr)
	{
		if (map[vars->i][vars->k] == ' ' && ((vars->k > 0 && map[vars->i][vars->k - 1] != '1' && map[vars->i][vars->k - 1] != ' ') ||
											 (vars->k < vars->len_curr - 1 && map[vars->i][vars->k + 1] != '1' && map[vars->i][vars->k + 1] != ' ')))
			return (0); // La carte n'est pas valide

		// Vérifier les règles de longueur de ligne
		if ((vars->len_curr > vars->len_top && vars->k >= vars->len_top && map[vars->i][vars->k] != '1') ||
			(vars->len_curr > vars->len_bottom && vars->k >= vars->len_bottom && map[vars->i][vars->k] != '1'))
			return (0); // La carte n'est pas valide
		vars->k++;
	}
	return (1);
}

int validate_line(char **map, int height, t_map_vars *vars)
{
	// Ignorer les espaces en début de ligne
	vars->j = 0;
	while (vars->j < vars->len_curr && map[vars->i][vars->j] == ' ')
		vars->j++;

	// Vérifier la première et la dernière ligne
	if (vars->i == 0 || vars->i == height - 1)
		return (validate_first_last_line(map, vars));
	else
		return (validate_middle_line(map, vars));
}

int validate_map(char **map, int height)
{
	t_map_vars vars;

	vars.i = 0;
	while (vars.i < height)
	{
		initialize_lengths(map, height, &vars);
		if (!validate_line(map, height, &vars))
			return (0);
		vars.i++;
	}
	return (1); // La carte est valide
}

/**********/

int	check_map(t_data *data)
{
	data->map = copy_map(data->fileinfo.copy_map, data);
	get_map_lenght_height(data);
	if (validate_map(data->map, data->fileinfo.map_height))
		printf("OK map closed\n");
	else
		exit_read(data, "Error: Map not closed\n");
	// flood_fill(data, data->pos_x, data->pos_y, data->fileinfo.copy_map);
	// print_map(data->fileinfo.copy_map);
	// check_flood_fill(data);
	// pas faire flood fill mais checker la premiere et derniere ligne en prenant en compte les esapces
	return (0);
}
