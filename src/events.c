/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:00:00 by erpascua          #+#    #+#             */
/*   Updated: 2025/11/26 11:25:46 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int	close_window(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_window(cub->mlx, cub->win);
	exit(0);
	return (0);
}

int	is_valid_position(t_cub *cub, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x / 20;
	map_y = (int)y / 20;
	if (map_x < 0 || map_x >= cub->map.width
		|| map_y < 0 || map_y >= cub->map.height)
		return (0);
	if (cub->map.grid[map_y][map_x] == '1')
		return (0);
	return (1);
}

int	key_press(int keycode, t_cub *cub)
{
	int		move_speed;
	double	player_angle_rad;
	double	move_x;
	double	move_y;
	double	new_x;
	double	new_y;

	move_speed = 5;	
	player_angle_rad = cub->player.player_dir * M_PI / 180.0;
	if (keycode == KEY_ESC)
		close_window(cub);
	else if (keycode == KEY_W)
	{
		move_x = cos(player_angle_rad) * move_speed;
		move_y = sin(player_angle_rad) * move_speed;
		new_x = cub->player.x_pos + move_x;
		new_y = cub->player.y_pos + move_y;		
		if (is_valid_position(cub, new_x, new_y))
		{
			cub->player.x_pos = new_x;
			cub->player.y_pos = new_y;
		}
	}
	else if (keycode == KEY_S)
	{
		move_x = cos(player_angle_rad) * move_speed;
		move_y = sin(player_angle_rad) * move_speed;
		new_x = cub->player.x_pos - move_x;
		new_y = cub->player.y_pos - move_y;
		if (is_valid_position(cub, new_x, new_y))
		{
			cub->player.x_pos = new_x;
			cub->player.y_pos = new_y;
		}
	}
	else if (keycode == KEY_A)
	{
		move_x = cos(player_angle_rad - M_PI/2) * move_speed;
		move_y = sin(player_angle_rad - M_PI/2) * move_speed;
		new_x = cub->player.x_pos + move_x;
		new_y = cub->player.y_pos + move_y;
		if (is_valid_position(cub, new_x, new_y))
		{
			cub->player.x_pos = new_x;
			cub->player.y_pos = new_y;
		}
	}
	else if (keycode == KEY_D)
	{
		move_x = cos(player_angle_rad + M_PI/2) * move_speed;
		move_y = sin(player_angle_rad + M_PI/2) * move_speed;
		new_x = cub->player.x_pos + move_x;
		new_y = cub->player.y_pos + move_y;
		if (is_valid_position(cub, new_x, new_y))
		{
			cub->player.x_pos = new_x;
			cub->player.y_pos = new_y;
		}
	}
	else if (keycode == KEY_LEFT)
	{
		cub->player.player_dir -= 1.0;
		if (cub->player.player_dir < 0)
			cub->player.player_dir += 360.0;
	}
	else if (keycode == KEY_RIGHT)
	{
		cub->player.player_dir += 1.0;
		if (cub->player.player_dir >= 360.0)
			cub->player.player_dir -= 360.0;
	}
	render(cub);
	return (0);
}
