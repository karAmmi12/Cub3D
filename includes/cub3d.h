/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:13:36 by apintus           #+#    #+#             */
/*   Updated: 2024/10/02 18:34:21 by kammi            ###   ########.fr       */
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
#define M_PI 3.14159265358979323846
#define PINK 0xFFC0CB
#define WHITE 0x00FFFFFF
#define BLACK 0x00000000
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define YELLOW 0x00FFFF00
#define PURPLE 0x00800080
#define GREY 0x00A9A9A9
#define BLACK 0x00000000
#define LMB 1
#define RMB 3
#define KEY_A 97
#define KEY_D 100
#define KEY_W 119
#define KEY_S 115
#define KEY_ESC 65307
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define FOV_ANGLE 60
#define RAY_COUNT 640
#define MOVE_SPEED 10
#define ROTATE_SPEED 0.1
#define RENDER_DISTANCE 50 // en cellule

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

typedef struct s_ray
{
	t_vector2_f	hit_point;
	t_vector2_d	cell;
	double		len;
	int			side_hit;
	double		angle;
	double		perp_len;
}	t_ray;

typedef struct s_player
{
	t_vector2_f	pos;
	t_vector2_d	view_dis_pos;
	t_vector2_f	dir;
}	t_player;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*win2;
	int		win_height;
	int		win_width;
	t_file	fileinfo;
	char	**map;
	char	*bigline;
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
	// image 2
	void	*img2;
	char	*addr2;
	int		bits_per_pixel2;
	int		line_length2;
	int		endian2;
	// keyboard
	int	keyboard[203];
	int	mouse_button;
	int	mouse_x;
	int	mouse_y;
	// tab
	int	**tab;
	int	tab_width;
	int	tab_height;
	int	cell_size;
	// ray
	t_ray	*ray_array;
	int		ray_count;
	int		view_dst;
	float	*ray_angles;
	t_player	player;
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

void	set_grid_cell(t_data *data, int x, int y);
int	perform_raycasting(t_data *data);
int	player_input(t_data *data);
double	degree_to_radian(double degree);
void	rays_render(t_data *data);
void	draw_rect_color(t_data *data, t_vector2_d top_left, t_vector2_d bottom_right, int color);
// Init Game
void	init_game(t_data *data);
void	init_player(t_data *data);
void	init_rays(t_data *data);
int		init_tab(t_data *data, char **map);

// Vector Utils
double	get_angle(t_vector2_d origin, int x, int y);
double	degree_to_radian(double degree);
t_vector2_f	create_vector_f_from_origin(t_vector2_f origin, double angle, int len);
t_vector2_f	vector_d_to_f(t_vector2_d v);
t_vector2_f	vector_f_lerp(t_vector2_f a, t_vector2_f b, double t);
float	get_vector_d_length_squared(t_vector2_d a, t_vector2_d b);
double	get_vector_f_len(t_vector2_d origin, t_vector2_f dst);

// Movement
int	input_key(t_data *data);
int	rotate_left(t_data *data);
int	rotate_right(t_data *data);
int	move_forward(t_data *data);
int	move_backward(t_data *data);
int	move_left(t_data *data);
int	move_right(t_data *data);
int is_colliding(t_data *data, float x, float y);

// Coloriage ou Drawing (j hesite)
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_rect_color(t_data *data, t_vector2_d top_left, t_vector2_d bottom_right, int color);
void	floor_and_ceiling(t_data *data);
int		rgb_to_mlx(int t, int r, int g, int b);


// 2d
void	draw_square(t_data *data, int x, int y, int color);
void	print_grind(t_data *data);
void	bresenham(t_data *data, t_vector2_d origin, t_vector2_f dst, int color);
void	my_mlx_pixel_put2(t_data *data, int x, int y, int color);
void	draw_rect_color2(t_data *data, t_vector2_d top_left, t_vector2_d bottom_right, int color);

#endif
