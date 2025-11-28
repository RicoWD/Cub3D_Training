/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 02:08:20 by ubuntu            #+#    #+#             */
/*   Updated: 2025/11/28 16:56:24 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// t_ray	raycaster(t_cub *cub, double ray_angle)
// {
// 	t_ray	ray;
// 	(void)cub;
// 	(void)ray_angle;
// 	return (ray);
// }

void	draw_column(t_cub *cub, t_ray *ray, int x)
{
	(void)cub;
	(void)ray;
	(void)x;
}

void	render_3d(t_cub *cub)
{
	int	x;
	double	ray_angle;
	double	angle_increment;
	t_ray	ray;
	
	x = 0;
	angle_increment = FOV_ANGLE / WIN_WIDTH;
	
	while (x < WIN_WIDTH)
	{
		ray_angle = (cub->player.player_dir * M_PI / 180.0) - (FOV_ANGLE / 2.0) + (x * angle_increment);
		ray = raycaster(cub, ray_angle);
		draw_column(cub, &ray, x);
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}

