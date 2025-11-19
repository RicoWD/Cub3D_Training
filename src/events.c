/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 00:00:00 by erpascua          #+#    #+#             */
/*   Updated: 2025/11/19 16:07:19 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdlib.h>

int	close_window(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_window(cub->mlx, cub->win);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_cub *cub)
{
	int	move_speed;

	move_speed = 5;
	if (keycode == KEY_ESC)
		close_window(cub);
	else if (keycode == KEY_UP || keycode == KEY_W)
		cub->player.y_pos -= move_speed;
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		cub->player.y_pos += move_speed;
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		cub->player.x_pos -= move_speed;
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		cub->player.x_pos += move_speed;
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
