/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:00:00 by erpascua          #+#    #+#             */
/*   Updated: 2025/11/25 19:41:30 by erpascua         ###   ########.fr       */
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
	double	fov_change;
	double	angle_change;

	move_speed = 5;
	fov_change = 0.05;
	angle_change = 5.0;
	if (keycode == KEY_ESC)
		close_window(cub);
	else if (keycode == KEY_W)
		cub->player.y_pos -= move_speed;
	else if (keycode == KEY_S)
		cub->player.y_pos += move_speed;
	else if (keycode == KEY_A)
		cub->player.x_pos -= move_speed;
	else if (keycode == KEY_D)
		cub->player.x_pos += move_speed;
	
	else if (keycode == KEY_UP)
	{
		cub->player.fov = fmax(0.3, cub->player.fov - fov_change);
		if (cub->player.angle > -45.0)
			cub->player.angle -= angle_change;
		printf("UP: angle=%.1f°, fov=%.2f\n", cub->player.angle, cub->player.fov);
	}
	else if (keycode == KEY_DOWN)
	{
		cub->player.fov = fmin(2.5, cub->player.fov + fov_change);
		if (cub->player.angle < 45.0)
			cub->player.angle += angle_change;
		printf("DOWN: angle=%.1f°, fov=%.2f\n", cub->player.angle, cub->player.fov);
	}
	else if (keycode == KEY_LEFT)
	{
		printf("PLAYER_DIR |%f|", cub->player.player_dir);
		cub->player.player_dir -= 5;
		if (cub->player.player_dir < 0)
			cub->player.player_dir += 360.0;
		printf("LEFT: player_dir=%.1f°\n", cub->player.player_dir);
	}
	else if (keycode == KEY_RIGHT)
	{
		printf("PLAYER_DIR |%f|", cub->player.player_dir);
		cub->player.player_dir += 5;
		if (cub->player.player_dir >= 360.0)
			cub->player.player_dir -= 360.0;
		printf("RIGHT: player_dir=%.1f°\n", cub->player.player_dir);
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
