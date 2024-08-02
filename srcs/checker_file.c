/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:43:19 by apintus           #+#    #+#             */
/*   Updated: 2024/07/31 13:10:55 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

int	check_ext_cub(char *str)
{
	if (str[0] == '.')
		return (1);
	while (*str != '.' && *str != '\0')
		str++;
	if (*str == '.')
	{
		str++;
		if (ft_strlen(str) == 3)
		{
			if (str[0] == 'c' && str[1] == 'u' && str[2] == 'b')
				return (0);
		}
	}
	return (1);
}

int	check_ext_xpm(char *str)
{
	if (str[0] == '.')
		return (1);
	while (*str != '.' && *str != '\0')
		str++;
	if (*str == '.')
	{
		str++;
		if (ft_strlen(str) == 3)
		{
			if (str[0] == 'x' && str[1] == 'p' && str[2] == 'm')
				return (0);
		}
	}
	return (1);
}

int	is_directory(char *str)
{
	int	fd;
	int	ret;

	ret = 0;
	fd = open(str, __O_DIRECTORY);
	if (fd > 0)
	{
		ret = 1;
		close(fd);
	}
	return (ret);
}

int	check_file(t_data *data, char *file_name)
{
	int	fd;

	if (is_directory(file_name))
		exit_read(data, "Error: File is a directory\n");
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit_read(data, "Error: File not found\n");
	close(fd);
	printf("OK file\n"); // a supp
	return (0);
}