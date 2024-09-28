/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:13:25 by apintus           #+#    #+#             */
/*   Updated: 2024/09/27 17:53:52 by apintus          ###   ########.fr       */
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

// void	init_ray_struct(t_data *data)
// {
// 	data->win = NULL;
// 	data->mlx = NULL;
// 	data->ray.px = data->pos_x;
// 	data->ray.py = data->pos_y;
// 	if (data->fileinfo.n_flag)
// 		data->ray.ra = 3 * PI / 2;
// 	else if (data->fileinfo.s_flag)
// 		data->ray.ra = PI / 2;
// 	else if (data->fileinfo.e_flag)
// 		data->ray.ra = PI;
// 	else if (data->fileinfo.w_flag)
// 		data->ray.ra = 0;
// }

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
	// init_ray_struct(data);
	data->cell_size = 40;
	data->win_height = 1080;
	data->win_width = 1920;
}

void	init_rays(t_data *data)
{
	int		i;
	double	angle_step;

	i = 0;
	data->ray_count = FOV_ANGLE;
	data->view_dst = RENDER_DISTANCE * data->cell_size;
	data->ray_array = malloc(sizeof(t_ray) * data->ray_count);
	if (data->ray_array == NULL)
		exit_read(data, "Error: malloc failed\n");
	angle_step = FOV_ANGLE / data->ray_count; // = 1 useless
	while (i < data->ray_count)
	{
		data->ray_array[i].angle = -FOV_ANGLE / 2 + i * angle_step;
		i++;
	}
	data->ray_angles = malloc(sizeof(float) * data->ray_count);
	if (data->ray_angles == NULL)
		exit_read(data, "Error: malloc failed\n");
}

void	init_player(t_data *data)
{
	data->player.pos.x = (float)data->tab_width * (float)data->cell_size / 2.0f;
	data->player.pos.y = (float)data->tab_height * (float)data->cell_size / 2.0f;
	printf("player pos x: %f, y: %f\n", data->player.pos.x, data->player.pos.y);
	data->player.dir.x = 0;
	data->player.dir.y = -1; // norh
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
	// print_map(data->fileinfo.copy_map); //visu
	// 3 check map
	check_map(data);
	// 4 init map
	init_map(data);

	init_rays(data);
	init_tab(data);
	init_player(data);
	// 5 init mlx
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (exit_read(data, "Error: mlx init failed\n"), 1);
	// 6 init win
	data->win = mlx_new_window(data->mlx, 1920, 1080, "Cub3D");
	if (data->win == NULL)
		return (exit_read(data, "Error: mlx win failed\n"), 1);
	// 7 init image
	data->img = mlx_new_image(data->mlx, 1920, 1080);
	if (data->img == NULL)
		return (exit_read(data, "Error: mlx img failed\n"), 1);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	// TEST PIXEL
	// my_mlx_pixel_put(data, 100, 100, 0x00FF0000);
	// mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	// 8 init tab
	
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
