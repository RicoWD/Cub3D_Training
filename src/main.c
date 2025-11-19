/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:23:04 by erpascua          #+#    #+#             */
/*   Updated: 2025/11/19 15:44:08 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	(void)ac;
	(void)av;
	cub.mlx = mlx_init();
	cub.win = mlx_new_window(cub.mlx, 800, 600, "Cub3D");
	cub.img.img = mlx_new_image(cub.mlx, 800, 600);
	cub.img.addr = mlx_get_data_addr(cub.img.img, &cub.img.bpp, 
		&cub.img.line_len, &cub.img.endian);
	init_map(&cub);
	render(&cub);
	mlx_hook(cub.win, 2, 1L<<0, key_press, &cub);
	mlx_hook(cub.win, 17, 0, close_window, &cub);
	mlx_loop(cub.mlx);
}
