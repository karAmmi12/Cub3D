/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:13:25 by apintus           #+#    #+#             */
/*   Updated: 2024/08/01 17:32:54 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 * 1- Lire fichier .cub et stocker les infos de texture, couleur et map
 * 2- Verifier si les infos sont valide et map correct
 * 3- init la map
 * 4- faire les touches (deplacement, fermer fenetre etc)
 * 5- faire des maths avec la camera
 * 6- tous free pour quitter bien
*/

void	read_file(t_data *data)
{
	int	i;

	i = 0;
	while (data->fileinfo.file[i])
	{
		printf("%s\n", data->fileinfo.file[i]);
		i++;
	}
}

void	init_data(t_data *data)
{
	data->fileinfo.file = NULL;
	data->fileinfo.north = NULL;
	data->fileinfo.south = NULL;
	data->fileinfo.west = NULL;
	data->fileinfo.east = NULL;
	data->fileinfo.floor[0] = -1;
	data->fileinfo.floor[1] = -1;
	data->fileinfo.floor[2] = -1;
	data->fileinfo.celling[0] = -1;
	data->fileinfo.celling[1] = -1;
	data->fileinfo.celling[2] = -1;
	data->bigline = NULL;
	data->fileinfo.verif.north = 0;
	data->fileinfo.verif.south = 0;
	data->fileinfo.verif.east = 0;
	data->fileinfo.verif.west = 0;
	data->fileinfo.verif.floor = 0;
	data->fileinfo.verif.celling = 0;
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (ft_putstr_fd("Malloc error\n", 2), 1);
	if (ac != 2 || check_ext_cub(av[1]))
		return (free(data), ft_putstr_fd("Error: Wrong arg or extension\n", 2), 1);
	printf("OK extension\n"); // a supp
	if (check_file(data, av[1]))
		return (free(data), 1);
	// 0 - init data
	init_data(data);
	// 1- recup les infos
	copy_file(data, av[1]);
	printf("OK copy file\n"); // a supp
	read_file(data);
	// 2- verifier les infos
	get_info(data->fileinfo.file, data);
	printf("OK get info\n"); // a supp
	// 3 check map
	check_map(data);
	return (0);
}
