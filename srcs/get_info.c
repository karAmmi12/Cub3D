/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:15:54 by apintus           #+#    #+#             */
/*   Updated: 2024/08/22 14:16:41 by apintus          ###   ########.fr       */
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
		if (data->fileinfo.n_flag == 1)
			exit_read(data, "Error :\nTexture north in double\n");
		data->fileinfo.north = ft_strdup(&str[i]);
		data->fileinfo.n_flag = 1;
	}
	else if (str[i] == 'S' && str[i + 1] == 'O')
	{
		i += 2;
		while (is_whitespace(str[i]))
			i++;
		if (data->fileinfo.s_flag == 1)
			exit_read(data, "Error :\nTexture south in double\n");
		data->fileinfo.south = ft_strdup(&str[i]);
		data->fileinfo.s_flag = 1;
	}
	else if (str[i] == 'W' && str[i + 1] == 'E')
	{
		i += 2;
		while (is_whitespace(str[i]))
			i++;
		if (data->fileinfo.w_flag == 1)
			exit_read(data, "Error :\nTexture west in double\n");
		data->fileinfo.west = ft_strdup(&str[i]);
		data->fileinfo.w_flag = 1;
	}
	else if (str[i] == 'E' && str[i + 1] == 'A')
	{
		i += 2;
		while (is_whitespace(str[i]))
			i++;
		if (data->fileinfo.e_flag == 1)
			exit_read(data, "Error :\nTexture east in double\n");
		data->fileinfo.east = ft_strdup(&str[i]);
		data->fileinfo.e_flag = 1;
	}
	printf("OK get texture\n"); // a supp
}

int	extract_colors(char *str, int *color)
{
	int		i;
	int		j;
	int		k;
	long	temp;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] != '\0' && j < 3)
	{
		while (is_whitespace(str[i]))
			i++;
		if ((j == 1 || j == 2) && str[i] != ',')
			return (-1); // Pas de virgule entre les nb
		if ((j == 1 || j == 2) && str[i] == ',')
			i++;
		while (is_whitespace(str[i]))
			i++;
		if (!ft_isdigit(str[i]) && !is_whitespace(str[i]))
			return (-1); // Pas un chiffre
		if ((str[i] >= '0' && str[i] <= '9'))
		{
			temp = ft_atoi(&str[i]);
			if (temp > INT_MAX)
				return (-1); // Overflow
			color[j] = (int)temp;
			printf("Color : %d\n", color[j]); // a supp
			j++;
			while (str[i] >= '0' && str[i] <= '9')
			{
				i++;
				k++;
				if (k > 10)
					return (-1); // Trop grand chiffre
			}
		}
		else
			i++;
	}
	if (j == 3)
		while (str[i] != '\0')
		{
			if (str[i] != ' ' && str[i] != '\t')
				return (-1); // Trop de couleurs
			i++;
		}
	return	(j); // Retourne le nombre de couleurs extraites
}

void get_color(char *str, t_data *data)
{
	int	i;
	int	color[3];
	int	flag;

	i = 0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == 'F' || str[i] == 'C')
	{
		flag = str[i];
		i++;
		while (is_whitespace(str[i]))
			i++;
		int num_colors = extract_colors(&str[i], color);
		if (num_colors != 3 || num_colors == -1)
		{
			exit_read(data, "Error :\nCode couleur non valide\n");
			return;
		}
		if (flag == 'F')
		{
			if (data->fileinfo.f_flag == 1)
				exit_read(data, "Error :\nCouleur de sol en double\n");
			data->fileinfo.floor[0] = color[0];
			data->fileinfo.floor[1] = color[1];
			data->fileinfo.floor[2] = color[2];
			data->fileinfo.f_flag = 1;
		}
		else if (flag == 'C')
		{
			if (data->fileinfo.c_flag == 1)
				exit_read(data, "Error :\nCouleur de plafond en double\n");
			data->fileinfo.celling[0] = color[0];
			data->fileinfo.celling[1] = color[1];
			data->fileinfo.celling[2] = color[2];
			data->fileinfo.c_flag = 1;
		}
	}
	printf("OK get color\n"); // a supp
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return (0);
	while (tab[i] != NULL)
		i++;
	return (i);
}

void	get_map(char **file_copy, int i, t_data *data)
{
	int	j;
	int	len;

	j = 0;
	check_before_map(data);
	len = ft_tablen(file_copy);
	data->fileinfo.copy_map = malloc(sizeof(char *) * (len - i + 1));
	if (data->fileinfo.copy_map == NULL)
		exit_read(data, "Error: Malloc error\n");
	printf("VERIF MAPPPP\n");
	while (file_copy[i] != NULL) // essayer i < len
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
