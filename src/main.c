/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:23:04 by erpascua          #+#    #+#             */
/*   Updated: 2025/11/17 16:02:12 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;

	(void)ac;
	(void)av;
	mlx = mlx_init();
	ft_fprintf(1, "STEP 0: mlx_init done\n");
	win = mlx_new_window(mlx, 800, 600, "Cub3D");
	ft_fprintf(1, "STEP 1: mlx_new_window done\n");
	img = mlx_new_image(mlx, 800, 600);
	ft_fprintf(1, "STEP 2: mlx_new_image done\n");
	addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);
	(void)addr;
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	ft_fprintf(1, "STEP 3: mlx_put_image_to_window done\n");
	ft_fprintf(1, "PROGRAM LAUNCHED\n");
	mlx_loop(mlx);
}
