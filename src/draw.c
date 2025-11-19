/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:00:00 by erpascua          #+#    #+#             */
/*   Updated: 2025/11/19 19:03:18 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	draw_fov(t_img img, t_player p)
{

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
				draw_square(&cub->img, j * tile_size, i * tile_size, 
					tile_size, COLOR_WHITE);
			else if (cub->map.grid[i][j] == '0')
				draw_square(&cub->img, j * tile_size, i * tile_size, 
					tile_size, COLOR_BLACK);
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
	my_mlx_pixel_put(&cub->img, (int)cub->player.x_pos - 5, 
		(int)cub->player.y_pos - 5, COLOR_RED);
	// draw_square(&cub->img, (int)cub->player.x_pos - 5, 
	// 	(int)cub->player.y_pos - 5, 10, COLOR_RED);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}
