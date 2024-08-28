/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:52:50 by apintus           #+#    #+#             */
/*   Updated: 2024/08/28 15:20:03 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	onlywhitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\v' && str[i] != '\f' && str[i] != '\r')
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
	// if (data->map == NULL)          // a voir si on le laisse
	// 	exit_read(data, "Error :\nEmpty map\n");
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
		exit_read(data, "Error :\n Empty map\n"); // pas de map
	copy_map = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
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

/*******fonction decouper0 ******************/

// void	initialize_lengths(char **map, int height, t_map_vars *vars)
// {
// 	vars->len_curr = strlen(map[vars->i]); // Longueur de la ligne actuelle
// 	if (vars->i > 0)
// 		vars->len_top = strlen(map[vars->i - 1]); // Longueur de la ligne précédente
// 	else
// 		vars->len_top = 0;

// 	if (vars->i < height - 1)
// 		vars->len_bottom = strlen(map[vars->i + 1]); // Longueur de la ligne suivante
// 	else
// 		vars->len_bottom = 0;
// }

// int	validate_first_last_line(char **map, t_map_vars *vars)
// {
// 	vars->k = vars->j;
// 	while (vars->k < vars->len_curr)
// 	{
// 		if (map[vars->i][vars->k] != '1' && map[vars->i][vars->k] != ' ')
// 			return (0); // La carte n'est pas valide
// 		vars->k++;
// 	}
// 	return (1);
// }

// int	validate_middle_line(char **map, t_map_vars *vars)
// {
// 	// Vérifier que le premier et le dernier caractère sont des '1'
// 	if (map[vars->i][vars->j] != '1' || map[vars->i][vars->len_curr - 1] != '1')
// 		return (0); // La carte n'est pas valide

// 	// Vérifier les caractères adjacents aux espaces
// 	vars->k = vars->j;
// 	while (vars->k < vars->len_curr)
// 	{
// 		if (map[vars->i][vars->k] == ' ' && ((vars->k > 0 && map[vars->i][vars->k - 1] != '1' && map[vars->i][vars->k - 1] != ' ') ||
// 											 (vars->k < vars->len_curr - 1 && map[vars->i][vars->k + 1] != '1' && map[vars->i][vars->k + 1] != ' ')))
// 			return (0); // La carte n'est pas valide

// 		// Vérifier les règles de longueur de ligne
// 		if ((vars->len_curr > vars->len_top && vars->k >= vars->len_top && map[vars->i][vars->k] != '1') ||
// 			(vars->len_curr > vars->len_bottom && vars->k >= vars->len_bottom && map[vars->i][vars->k] != '1'))
// 			return (0); // La carte n'est pas valide
// 		vars->k++;
// 	}
// 	return (1);
// }

// int	validate_line(char **map, int height, t_map_vars *vars)
// {
// 	// Ignorer les espaces en début de ligne
// 	vars->j = 0;
// 	while (vars->j < vars->len_curr && map[vars->i][vars->j] == ' ')
// 		vars->j++;

// 	// Vérifier la première et la dernière ligne
// 	if (vars->i == 0 || vars->i == height - 1)
// 		return (validate_first_last_line(map, vars));
// 	else
// 		return (validate_middle_line(map, vars));
// }

/**************  V2 ****************/

int	can_escape(char **map, int i, int j, int height)
{
	int	flag;
	int	j_start;
	int	i_start;

	flag = 0;
	j_start = j;
	i_start = i;
	while (map[i][j]) // check right
	{
		if (map[i][j] == '1')
		{
			flag++;
			break;
		}
		j++;
	}
	j = j_start;
	while (i < height) // check down
	{
		if (map[i][j] == '1')
		{
			flag++;
			break;
		}
		i++;
	}
	i = i_start;
	while (j >= 0) // check left
	{
		if (map[i][j] == '1')
		{
			flag++;
			break;
		}
		j--;
	}
	j = j_start;
	while (i >= 0) // check up
	{
		if (map[i][j] == '1')
		{
			flag++;
			break;
		}
		i--;
	}
	if (flag == 4)
		return (0);
	return (1);
}

int	check_hole(char **map, int height, t_data *data)
{
	int	i;
	int	j;
	int	flag;

	(void)data;
	flag = 0;
	i = 0;
	j = 0;
	while(map[i][j])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == '0')
				flag = can_escape(map, i, j, height);
			if (flag)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/**************************/

int	handle_player_count(char **map, int height, t_data *data, t_map_vars *vars)
{
	vars->player_count = 0;
	vars->i = 0;
	while (vars->i < height)
	{
		vars->j = 0;
		while (map[vars->i][vars->j])
		{
			if (map[vars->i][vars->j] == 'N' || map[vars->i][vars->j] == 'S' ||
				map[vars->i][vars->j] == 'E' || map[vars->i][vars->j] == 'W')
			{
				data->pos_x = vars->j;
				data->pos_y = vars->i;
				vars->player_count++;
			}
			vars->j++;
		}
		vars->i++;
	}
	if (vars->player_count != 1)
	{
		printf("Error: There must be exactly one playe)r start position (N, S, E, W).\n");
		return (0);
	}
	return (1);
}

int	last_check_map(char **map, int height)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[0][j])
	{
		if (map[0][j] == ' ' && map[1][j] == '0')
		{
			printf("Error: Map is not closed1\n");
			return (1);
		}
		j++;
	}
	j = 0;
	while (map[height - 1][j])
	{
		if (map[height - 1][j] == ' ' && map[height - 2][j] == '0')
		{
			printf("Error: Map is not closed2\n");
			return (1);
		}
		j++;
	}
	return (0);
}

int	other_caracter(char **map, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ' &&
				map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' &&
				map[i][j] != 'W')
			{
				printf("Error: Invalid character in map\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map(char **map, int height, t_data *data)
{
	t_map_vars vars;

	vars.i = 0;
	printf("HEIGHT %d\n", height); // a supp
	// while (vars.i < height)
	// {
	// 	initialize_lengths(map, height, &vars);
	// 	if (!validate_line(map, height, &vars))
	// 	{
	// 		printf("Error: Map is not closed3\n");
	// 		return (0);
	// 	}
	// 	vars.i++;
	// }
	if (check_hole(map, height, data))
	{
		printf("Error: Map is not closed4\n");
		return (0);
	}
	if (!handle_player_count(map, height, data, &vars))
		return (0);
	if (other_caracter(map, height))
		return (0);
	if (last_check_map(map, height)) // patch espace debut 1ere et derniere ligne
		return (0);
	return (1); // La carte est valide
}

/**********/
int	check_map(t_data *data)
{
	data->map = copy_map(data->fileinfo.copy_map, data);
	get_map_lenght_height(data);
	if (validate_map(data->map, data->fileinfo.map_height, data))
		printf("OK map closed\n");
	else
		clean_exit(data, 1);
	return (0);
}
