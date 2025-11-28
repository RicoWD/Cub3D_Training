/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:50:06 by erpascua          #+#    #+#             */
/*   Updated: 2025/11/28 17:16:47 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "player.h"
# include <mlx.h>
# include <stdio.h>
# include <stdbool.h>


# ifdef __APPLE__
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_Q 12
#  define KEY_E 14
#  define KEY_R 15
#  define KEY_F 3
# else
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_Q 113
#  define KEY_E 101
#  define KEY_R 114
#  define KEY_F 102
# endif

# define _USE_MATH_DEFINES
# define _GNU_SOURCE

# ifndef M_PI
# 	define M_PI 3.14159265358979323846
# endif

# define ANGLE M_PI_4

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define COLOR_RED 0x00FF0000
# define COLOR_WHITE 0x00FFFFFF
# define COLOR_BLACK 0x00000000
# define COLOR_GOLD 0x00FFD700

# define FOV_ANGLE (60.0 * M_PI / 180.0)

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct	s_map
{
	char	**grid;
	int		width;
	int		height;
}				t_map;

typedef struct	s_cub
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_player		player;
	t_map			map;
}				t_cub;

typedef struct s_ray
{
    double	distance;
    bool	hit_wall;
    double	hit_x;
    double	hit_y;
    int		side;
}               t_ray;

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_square(t_img *img, int x, int y, int size, int color);
void	draw_map(t_cub *cub);
double	draw_fov(t_cub *cub);
void	render(t_cub *cub);
void	render_3d(t_cub *cub);
t_ray	raycaster(t_cub *cub, double ray_angle);
void	draw_column(t_cub *cub, t_ray *ray, int x);

int		key_press(int keycode, t_cub *cub);
int		close_window(t_cub *cub);

void	init_map(t_cub *cub);

#endif