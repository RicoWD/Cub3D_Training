/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:23:04 by erpascua          #+#    #+#             */
/*   Updated: 2025/11/19 02:23:22 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	(void)ac;
	(void)av;
	/* Initialisation de la MLX */
	cub.mlx = mlx_init();
	ft_fprintf(1, "STEP 0: mlx_init done\n");
	cub.win = mlx_new_window(cub.mlx, 800, 600, "Cub3D");
	ft_fprintf(1, "STEP 1: mlx_new_window done\n");
	
	/* Initialisation de l'image */
	cub.img.img = mlx_new_image(cub.mlx, 800, 600);
	ft_fprintf(1, "STEP 2: mlx_new_image done\n");
	cub.img.addr = mlx_get_data_addr(cub.img.img, &cub.img.bpp, 
		&cub.img.line_len, &cub.img.endian);
	
	/* Initialisation du joueur (centre de l'écran) */
	cub.player.x_pos = 400;
	cub.player.y_pos = 300;
	
	/* Premier rendu */
	render(&cub);
	ft_fprintf(1, "STEP 3: Initial render done\n");
	
	/* Configuration des événements */
	mlx_hook(cub.win, 2, 1L<<0, key_press, &cub);
	mlx_hook(cub.win, 17, 0, close_window, &cub);
	
	ft_fprintf(1, "PROGRAM LAUNCHED\n");
	ft_fprintf(1, "Utilisez les fleches ou WASD pour deplacer le point rouge\n");
	ft_fprintf(1, "Appuyez sur ESC pour quitter\n");
	mlx_loop(cub.mlx);
}
