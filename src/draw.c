/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:00:00 by erpascua          #+#    #+#             */
/*   Updated: 2025/11/24 02:28:05 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _USE_MATH_DEFINES
#define _GNU_SOURCE

#include "cub3D.h"
#include <math.h>


void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 800 || y < 0 || y >= 600)
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

void	draw_line(t_cub *cub, int end_x, int end_y, int color)
{
	double	dx;
	double	dy;
	double	steps;
	double	x;
	double	y;
	int		i;

	dx = end_x - cub->player.x_pos;
	dy = end_y - cub->player.y_pos;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	dx = dx / steps;
	dy = dy / steps;
	x = cub->player.x_pos;
	y = cub->player.y_pos;
	i = 0;
	while (i <= (int)steps)
	{
		my_mlx_pixel_put(&cub->img, (int)x, (int)y, color);
		x += dx;
		y += dy;
		i++;
	}
}

void	draw_fov(t_cub *cub)
{
	double	angle_rad_p;
	double	angle_rad_m;
	double	line_length;
	int		end_x_p;
	int		end_y_p;
	int		end_x_m;
	int		end_y_m;
	int		screen_width;
	int		screen_height;

	mlx_get_screen_size(cub->mlx, &screen_width, &screen_height);
	if (screen_width > screen_height)
		line_length = screen_width;
	else
		line_length = screen_height;
	angle_rad_p = (cub->player.player_dir + cub->player.angle + 22.5) * M_PI / 180.0;
	end_x_p = (int)(cub->player.x_pos + cos(angle_rad_p) * line_length);
	end_y_p = (int)(cub->player.y_pos + sin(angle_rad_p) * line_length);
	angle_rad_m = (cub->player.player_dir + cub->player.angle - 22.5) * M_PI / 180.0;
	end_x_m = (int)(cub->player.x_pos + cos(angle_rad_m) * line_length);
	end_y_m = (int)(cub->player.y_pos + sin(angle_rad_m) * line_length);
	draw_line(cub, end_x_p, end_y_p, COLOR_RED);
	draw_line(cub, end_x_m, end_y_m, COLOR_BLACK);
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
	while (i < 600)
	{
		j = 0;
		while (j < 800)
		{
			my_mlx_pixel_put(&cub->img, j, i, COLOR_GOLD);
			j++;
		}
		i++;
	}
	draw_map(cub);
	draw_fov(cub);
	my_mlx_pixel_put(&cub->img, (int)cub->player.x_pos,
		(int)cub->player.y_pos, COLOR_RED);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}
