/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintus <apintus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:13:36 by apintus           #+#    #+#             */
/*   Updated: 2024/08/22 18:11:00 by apintus          ###   ########.fr       */
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
#include <stdbool.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

/*********** STRUCTURES ***********/

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

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		win_height;
	int		win_width;
	t_file	fileinfo;
	char	**map;
	char	*bigline;
	int		pos_x;
	int		pos_y;
}	t_data;

/*********** PROTOTYPES ***********/

int	is_whitespace(char c);

int	check_ext_cub(char *str);
int	check_ext_xpm(char *str);

int	check_file(t_data *data, char *file_name);

void	exit_read(t_data *data, char *str);
void	clean_exit(t_data *data, int exit_code);

int	copy_file(t_data *data, char *filename);

int	get_info(char **file_copy, t_data *data);

int	check_before_map(t_data *data);

int	check_map(t_data *data);
int	ft_tablen(char **tab);

void	print_map(char **map);

#endif
