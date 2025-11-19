/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:00:00 by erpascua          #+#    #+#             */
/*   Updated: 2025/11/19 02:41:32 by ep               ###   ########.fr       */
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
	draw_square(&cub->img, (int)cub->player.x_pos - 5, 
		(int)cub->player.y_pos - 5, 10, COLOR_RED);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}
