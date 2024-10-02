/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:13:25 by apintus           #+#    #+#             */
/*   Updated: 2024/10/02 17:26:10 by apintus          ###   ########.fr       */
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

/*************** VISUALIZER ****************/

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
/*************** MAIN ****************/

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
	data->map = NULL;
	data->fileinfo.copy_map = NULL;
	data->fileinfo.map_height = 0;
	data->fileinfo.map_lenght = 0;
	data->pos_x = 0;
	data->pos_y = 0;
	data->fileinfo.n_flag = 0;
	data->fileinfo.s_flag = 0;
	data->fileinfo.e_flag = 0;
	data->fileinfo.w_flag = 0;
	data->fileinfo.f_flag = 0;
	data->fileinfo.c_flag = 0;
	data->cell_size = 64;
	data->win_height = 720;
	data->win_width = 1280;
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
	read_file(data); //visu
	// 2- verifier les infos
	get_info(data->fileinfo.file, data);
	printf("OK get info\n"); // a supp
	// 3 check map
	check_map(data);
	// 4 init GAMe
	init_game(data);
	// 5 init mlx
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (exit_read(data, "Error: mlx init failed\n"), 1);
	// 6 init win
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height, "Cub3D");
	if (data->win == NULL)
		return (exit_read(data, "Error: mlx win failed\n"), 1);
	data->win2 = mlx_new_window(data->mlx, data->win_width, data->win_height, "Cub2D");
	if (data->win2 == NULL)
		return (exit_read(data, "Error: mlx win failed\n"), 1);
	// 7 init image
	data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (data->img == NULL)
		return (exit_read(data, "Error: mlx img failed\n"), 1);
	data->img2 = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (data->img2 == NULL)
		return (exit_read(data, "Error: mlx img failed\n"), 1);
	// 8 init addr
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->addr2 = mlx_get_data_addr(data->img2, &data->bits_per_pixel2, &data->line_length2, &data->endian2);

	// mlx loop and hook
	mlx_loop_hook(data->mlx, perform_raycasting, data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 4, 1L << 2, mouse_press, data);
	mlx_hook(data->win, 5, 1L << 3, mouse_release, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->win, 17, 1L << 17, close_game, data);
	mlx_loop(data->mlx);
	// EXIT || CLEANNING
	clean_exit(data, 0);
	return (0);
}
