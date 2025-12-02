/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 02:08:20 by ubuntu            #+#    #+#             */
/*   Updated: 2025/12/02 02:18:02 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_column(t_cub *cub, t_ray *ray, int x)
{
	int		y;
	int		wall_height;
	int		start;
	int		end;
	double	projection_plane_dist;
	int		color;

	projection_plane_dist = (WIN_WIDTH / 2.0) / tan(FOV_ANGLE / 2.0);
	
	if (ray->distance <= 0.1)
		wall_height = WIN_HEIGHT;
	else
		wall_height = (int)((projection_plane_dist * TILE_SIZE) / ray->distance);
	start = (WIN_HEIGHT / 2) - (wall_height / 2);
	end = start + wall_height;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y < start)
			my_mlx_pixel_put(&cub->img, x, y, COLOR_SKY);
		else if (y > end)
			my_mlx_pixel_put(&cub->img, x, y, COLOR_FLOOR);
		else
		{
			if (ray->side == 0)
				color = COLOR_WALL_NS;
			else
				color = COLOR_WALL_EW;
			my_mlx_pixel_put(&cub->img, x, y, color);
		}
		y++;
	}
}

t_ray raycaster(t_cub *cub, double ray_angle)
{
    t_ray   ray;
    double  dx;
    double  dy;
    double  x;
    double  y;
    double  step;
    int     map_x;
    int     map_y;
    
    ray.hit_wall = 0;
    ray.distance = 0;
    dx = cos(ray_angle);
    dy = sin(ray_angle);
    x = cub->player.x_pos;
    y = cub->player.y_pos;
    step = 0.5;
    while (ray.distance < 1000)
    {
        x += dx * step;
        y += dy * step;
        ray.distance += step;
        
        map_x = (int)(x / TILE_SIZE);
        map_y = (int)(y / TILE_SIZE);        
        if (map_x < 0 || map_x >= cub->map.width || 
            map_y < 0 || map_y >= cub->map.height)
            break;
        if (cub->map.grid[map_y][map_x] == '1')
        {
            ray.hit_wall = 1;
            ray.hit_x = x;
            ray.hit_y = y;
            ray.side = 0;
            break;
        }
    }
    
    return (ray);
}

void	render_3d(t_cub *cub)
{
	int		x;
	double	ray_angle;
	double	angle_increment;
	double	player_angle;
	t_ray	ray;
	
	x = 0;
	angle_increment = FOV_ANGLE / WIN_WIDTH;
	player_angle = cub->player.player_dir * M_PI / 180.0;
	
	while (x < WIN_WIDTH)
	{
		ray_angle = player_angle - (FOV_ANGLE / 2.0) + (x * angle_increment);
		ray = raycaster(cub, ray_angle);
		
		// Correction fish-eye : très important !
		ray.distance *= cos(ray_angle - player_angle);
		
		draw_column(cub, &ray, x);
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}

