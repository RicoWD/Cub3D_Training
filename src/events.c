/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:00:00 by erpascua          #+#    #+#             */
/*   Updated: 2025/11/26 02:45:17 by ubuntu           ###   ########.fr       */
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

int	key_press(int keycode, t_cub *cub)
{
	int		move_speed;
	double	player_angle_rad;
	double	move_x;
	double	move_y;

	move_speed = 5;	
	player_angle_rad = cub->player.player_dir * M_PI / 180.0;
	if (keycode == KEY_ESC)
		close_window(cub);
	else if (keycode == KEY_W)
	{
		move_x = cos(player_angle_rad) * move_speed;
		move_y = sin(player_angle_rad) * move_speed;
		cub->player.x_pos += move_x;
		cub->player.y_pos += move_y;
	}
	else if (keycode == KEY_S)
	{
		move_x = cos(player_angle_rad) * move_speed;
		move_y = sin(player_angle_rad) * move_speed;
		cub->player.x_pos -= move_x;
		cub->player.y_pos -= move_y;
	}
	else if (keycode == KEY_A)
	{
		move_x = cos(player_angle_rad - M_PI/2) * move_speed;
		move_y = sin(player_angle_rad - M_PI/2) * move_speed;
		cub->player.x_pos += move_x;
		cub->player.y_pos += move_y;
	}
	else if (keycode == KEY_D)
	{
		move_x = cos(player_angle_rad + M_PI/2) * move_speed;
		move_y = sin(player_angle_rad + M_PI/2) * move_speed;
		cub->player.x_pos += move_x;
		cub->player.y_pos += move_y;
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
	if (cub->player.x_pos < 10)
		cub->player.x_pos = 10;
	if (cub->player.x_pos > 790)
		cub->player.x_pos = 790;
	if (cub->player.y_pos < 10)
		cub->player.y_pos = 10;
	if (cub->player.y_pos > 590)
		cub->player.y_pos = 590;
	render(cub);
	return (0);
}
