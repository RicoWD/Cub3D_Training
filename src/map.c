/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:30:00 by erpascua          #+#    #+#             */
/*   Updated: 2025/11/28 17:55:57 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && 
			line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && 
			line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static void	find_player(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (j < cub->map.width)
		{
			if (cub->map.grid[i][j] == 'N' || cub->map.grid[i][j] == 'S' ||
				cub->map.grid[i][j] == 'E' || cub->map.grid[i][j] == 'W')
			{
				cub->player.x_pos = j * 20 + 10;
				cub->player.y_pos = i * 20 + 10;
				cub->player.angle = 0.0;
				cub->player.fov = 1.0;
				if (cub->map.grid[i][j] == 'N')
					cub->player.player_dir = 270.0;
				else if (cub->map.grid[i][j] == 'S')
					cub->player.player_dir = 90.0;
				else if (cub->map.grid[i][j] == 'E')
					cub->player.player_dir = 0.0;
				else if (cub->map.grid[i][j] == 'W')
					cub->player.player_dir = 180.0;
				cub->map.grid[i][j] = '0';
				return;
			}
			j++;
		}
		i++;
	}
}

static void	parse_map_content(t_cub *cub, int fd)
{
	char	*line;
	char	**temp;
	int		count;
	int		i;

	temp = malloc(sizeof(char *) * 1000);
	count = 0;
	while ((line = get_next_line(fd)))
	{
		if (is_map_line(line) && line[0] == '1')
		{
			temp[count] = ft_strtrim(line, "\n");
			free(line);
			count++;
		}
		else
			free(line);
	}
	cub->map.height = count;
	cub->map.width = ft_strlen(temp[0]);
	cub->map.grid = malloc(sizeof(char *) * (count + 1));
	i = -1;
	while (++i < count)
		cub->map.grid[i] = temp[i];
	cub->map.grid[i] = NULL;
	free(temp);
	find_player(cub);
}

void	init_map(t_cub *cub)
{
	int	fd;

	fd = open("maps/map0.cub", O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nCannot open map file\n");
		exit(1);
	}
	parse_map_content(cub, fd);
	close(fd);
}
