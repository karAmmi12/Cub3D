/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:13:36 by apintus           #+#    #+#             */
/*   Updated: 2024/09/25 15:33:45 by apintus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <math.h>
# include "../mlx/mlx.h"

#define PI 3.1415926535
#define TWO_PI 6.28318530718
#define FOV_ANGLE 60
#define PINK 0xFFC0CB
#define WHITE 0x00FFFFFF
#define BLACK 0x00000000
#define LMB 1
#define RMB 3
#define KEY_ESC 65307

/*********** STRUCTURES ***********/

// struct de var pour la norme
typedef struct s_map_vars
{
	int	i;
	int	j;
	int	k;
	int	len_curr;
	int	len_top;
	int	len_bottom;
	int	player_count;
} t_map_vars;

// typedef struct s_verif // useless structure
// {
// 	int		north;
// 	int		south;
// 	int		east;
// 	int		west;
// 	int		floor;
// 	int		celling;
// }	t_verif;

// struct parsing
typedef struct s_file
{
	char	**file;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		floor[3];
	int		celling[3];
	char	**copy_map;
	int		map_height;
	int		map_lenght;
	int		n_flag;
	int		s_flag;
	int		e_flag;
	int		w_flag;
	int		f_flag;
	int		c_flag;
}	t_file;


// typedef struct s_ray
// {
// 	float	px; // Position X du joueur
// 	float	py; // Position Y du joueur
// 	float	xstep; // Pas en X
// 	float	ystep; // Pas en Y
// 	float	ax; // Angle X
// 	float	ay; // Angle Y
// 	float	ra; // Ray angle (angle du rayon)
// 	int		map_x; // Coordonnée X de la case de la grille
// 	int		map_y; // Coordonnée Y de la case de la grille
// 	float	side_dist_x; // Distance à parcourir jusqu'à la première intersection avec une ligne verticale de la grille en X
// 	float	side_dist_y; // Distance à parcourir jusqu'à la première intersection avec une ligne horizontale de la grille en Y
// 	float	delta_dist_x; // Distance à parcourir pour traverser une case de la grille en X
// 	float	delta_dist_y; // Distance à parcourir pour traverser une case de la grille en Y
// 	int		step_x; // Direction de déplacement en X
// 	int		step_y; // Direction de déplacement en Y
// 	float	perp_wall_dist; // Distance perpendiculaire au mur
// 	int		side; // Indicateur de la direction du mur (0 pour X, 1 pour Y)
// }	t_ray;

typedef struct s_ray
{
}	t_ray;

typedef struct s_vector2_d
{
	int	x;
	int	y;
}	t_vector2_d;

typedef struct s_vector2_f
{
	float	x;
	float	y;
}	t_vector2_f;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		win_height;
	int		win_width;
	t_file	fileinfo;
	char	**map;
	char	*bigline;
	t_ray	ray;
	float		pos_x;
	float		pos_y;
	int		mapHeight;
	int		mapWidth;
	// TUTO
	// image
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	// keyboard
	int	keyboard[200];
	int	mouse_button;
	int	mouse_x;
	int	mouse_y;
	// tab
	int	**tab;
	int	tab_width;
	int	tab_height;
	int	cell_size;
}	t_data;

/*********** PROTOTYPES ***********/

int	is_whitespace(char c);

int	check_ext_cub(char *str);
int	check_ext_xpm(char *str);

int	check_file(t_data *data, char *file_name);

void	exit_read(t_data *data, char *str);
void	clean_exit(t_data *data, int exit_code);
int		close_game(t_data *data);


int	copy_file(t_data *data, char *filename);

int	get_info(char **file_copy, t_data *data);

void	get_texture(char *str, t_data *data);

void	get_color(char *str, t_data *data);

int	check_before_map(t_data *data);

int	check_map(t_data *data);
int	ft_tablen(char **tab);

int	can_escape(char **map, int i, int j, int height);

char	**copy_map(char **map, t_data *data);
void	get_map_lenght_height(t_data *data);
int	onlywhitespace(char *str);


void	init_map(t_data *data);
void	print_map(char **map);

int	perform_raycasting(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

int	key_release(int keycode, t_data *data);
int	key_press(int keycode, t_data *data);
int	mouse_press(int button, int x, int y, t_data *data);
int	mouse_release(int button, int x, int y, t_data *data);
int	mouse_move(int x, int y, t_data *data);

int	init_tab(t_data *data);
void	set_grid_cell(t_data *data, int x, int y);
int	perform_raycasting(t_data *data);

#endif
