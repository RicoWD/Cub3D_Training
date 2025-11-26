/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:00:00 by erpascua          #+#    #+#             */
/*   Updated: 2025/11/26 16:26:33 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _USE_MATH_DEFINES
#define _GNU_SOURCE

#include "cub3D.h"
#include <math.h>

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_img *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

double	draw_line(t_cub *cub, int end_x, int end_y, int color)
{
	double	dx;
	double	dy;
	double	steps;
	double	x;
	double	y;
	int		i;
	int		map_x;
	int		map_y;

	dx = end_x - cub->player.x_pos;
	dy = end_y - cub->player.y_pos;
	steps = fabs(dx);
	dx = dx / steps;
	dy = dy / steps;
	x = cub->player.x_pos;
	y = cub->player.y_pos;
	i = 0;
	while (i <= (int)steps)
	{
		map_x = (int)x / 20;
		map_y = (int)y / 20;
		if (map_x >= 0 && map_x < cub->map.width && 
		    map_y >= 0 && map_y < cub->map.height)
		{
			if (cub->map.grid[map_y][map_x] == '1')
				break;
		}
		if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
			my_mlx_pixel_put(&cub->img, (int)x, (int)y, color);
		x += dx;
		y += dy;
		i++;
	}
	dx = x - cub->player.x_pos;
	dy = y - cub->player.y_pos;
	double distance = sqrt(dx * dx + dy * dy);
	return (distance);
}

void	draw_fov(t_cub *cub)
{
	double	angle_rad_p;
	double	angle_rad_m;
	int		tmp_endx;
	int		tmp_endy;
	double	base_angle;

	double	increment = ANGLE / WIN_WIDTH;
	base_angle = (cub->player.player_dir * M_PI / 180.0) + (cub->player.angle * M_PI / 180.0);
	angle_rad_p = base_angle + (ANGLE / 2);
	angle_rad_m = base_angle - (ANGLE / 2);
	while (angle_rad_m <= angle_rad_p)
	{
		tmp_endx = (int)(cub->player.x_pos + cos(angle_rad_m) * WIN_WIDTH);
		tmp_endy = (int)(cub->player.y_pos + sin(angle_rad_m) * WIN_WIDTH);
		double tmp = draw_line(cub, tmp_endx, tmp_endy, COLOR_RED);
		printf("Line distance : |%f|\n", tmp);
		angle_rad_m += increment;
	}
}

void	draw_map(t_cub *cub)
{
	int	i;
	int	j;
	int	tile_size;

	tile_size = 20;
	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (j < cub->map.width)
		{
			if (cub->map.grid[i][j] == '1')
				draw_square(&cub->img, j * tile_size, i * tile_size, tile_size,
					COLOR_WHITE);
			else if (cub->map.grid[i][j] == '0')
				draw_square(&cub->img, j * tile_size, i * tile_size, tile_size,
					COLOR_BLACK);
			j++;
		}
		i++;
	}
}

void	render(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			my_mlx_pixel_put(&cub->img, j, i, COLOR_GOLD);
			j++;
		}
		i++;
	}
	draw_map(cub);
	draw_fov(cub);
	my_mlx_pixel_put(&cub->img, (int)cub->player.x_pos, (int)cub->player.y_pos,
		COLOR_RED);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}
