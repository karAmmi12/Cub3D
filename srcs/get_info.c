/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:15:54 by apintus           #+#    #+#             */
/*   Updated: 2024/08/01 13:51:36 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/cub3d.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' ||
			c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	get_texture(char *str, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == 'N' && str[i + 1] == 'O')
	{
		i += 2;
		while (is_whitespace(str[i]))
			i++;
		data->fileinfo.north = ft_strdup(&str[i]);
	}
	else if (str[i] == 'S' && str[i + 1] == 'O')
	{
		i += 2;
		while (is_whitespace(str[i]))
			i++;
		data->fileinfo.south = ft_strdup(&str[i]);
	}
	else if (str[i] == 'W' && str[i + 1] == 'E')
	{
		i += 2;
		while (is_whitespace(str[i]))
			i++;
		data->fileinfo.west = ft_strdup(&str[i]);
	}
	else if (str[i] == 'E' && str[i + 1] == 'A')
	{
		i += 2;
		while (is_whitespace(str[i]))
			i++;
		data->fileinfo.east = ft_strdup(&str[i]);
	}
	printf("OK get texture\n"); // a supp
}

void	get_color(char *str, t_data *data)
{
	int	i;
	int	j;
	int	color[3];

	i = 0;
	j = 0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == 'F')
	{
		i++;
		while (is_whitespace(str[i]))
			i++;
		while (str[i] != '\0')
		{
			if (str[i] >= '0' && str[i] <= '9')
			{
				color[j] = ft_atoi(&str[i]);
				j++;
				while (str[i] >= '0' && str[i] <= '9')
					i++;
			}
			i++;
		}
		data->fileinfo.floor[0] = color[0];
		data->fileinfo.floor[1] = color[1];
		data->fileinfo.floor[2] = color[2];
	}
	else if (str[i] == 'C')
	{
		i++;
		while (is_whitespace(str[i]))
			i++;
		while (str[i] != '\0')
		{
			if (str[i] >= '0' && str[i] <= '9')
			{
				color[j] = ft_atoi(&str[i]);
				j++;
				while (str[i] >= '0' && str[i] <= '9')
					i++;
			}
			i++;
		}
		data->fileinfo.celling[0] = color[0];
		data->fileinfo.celling[1] = color[1];
		data->fileinfo.celling[2] = color[2];
	}
	printf("OK get color\n"); // a supp
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

void	get_map(char **file_copy, int i, t_data *data)
{
	int	j;

	j = 0;
	check_before_map(data);
	data->fileinfo.copy_map = malloc(sizeof(char *) * (ft_tablen(file_copy) - i + 1));
	if (data->fileinfo.copy_map == NULL)
		exit_read(data, "Error: Malloc error\n");
	while (file_copy[i] != NULL)
	{
		data->fileinfo.copy_map[j] = ft_strdup(file_copy[i]);
		i++;
		j++;
	}
	data->fileinfo.copy_map[j] = NULL;
	printf("OK get map\n"); // a supp
}

int	get_info(char **file_copy, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (file_copy[i] != NULL)
	{
		j = 0;
		while (is_whitespace(file_copy[i][j]))
			j++;
		printf("%c\n", file_copy[i][j]);
		if (file_copy[i][j] == 'N' && file_copy[i][j + 1] == 'O')
			get_texture(file_copy[i], data);
		else if (file_copy[i][j] == 'S' && file_copy[i][j + 1] == 'O')
			get_texture(file_copy[i], data);
		else if (file_copy[i][j] == 'W' && file_copy[i][j + 1] == 'E')
			get_texture(file_copy[i], data);
		else if (file_copy[i][j] == 'E' && file_copy[i][j + 1] == 'A')
			get_texture(file_copy[i], data);
		else if (file_copy[i][j] == 'F')
			get_color(file_copy[i], data);
		else if (file_copy[i][j] == 'C')
			get_color(file_copy[i], data);
		else if (file_copy[i][j] == '1')
		{
			get_map(file_copy, i, data);
			break ;
		}
		else if (file_copy[i][j] != '\0')
			exit_read(data, "Error: Wrong info\n");
		i++;
	}
	return (0);
}
