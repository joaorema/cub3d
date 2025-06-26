/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_set_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:50:15 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/26 21:50:16 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	find_player(t_game *game)
{
	int		x;
	int		y;
	char	cell;

	y = 0;
	while (y < game->map_height)
	{
		if (!game->map[y])
			y++;
		x = 0;
		while (game->map[y][x] != '\0')
		{
			cell = game->map[y][x];
			if (cell == 'N' || cell == 'S' || cell == 'W' || cell == 'E')
			{
				set_player_start(game, x, y, cell);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	set_player_start(t_game *game, int x, int y, char dir)
{
	game->player.tile_x = x;
	game->player.tile_y = y;
	game->player.position.x = x * TILE_SIZE + TILE_SIZE / 2;
	game->player.position.y = y * TILE_SIZE + TILE_SIZE / 2;
	set_player_angle(game, dir);
}

void	set_player_angle(t_game *game, char dir)
{
	if (dir == 'N')
		game->player_angle = 4.71238898038f;
	else if (dir == 'S')
		game->player_angle = 1.57079632679f;
	else if (dir == 'W')
		game->player_angle = 3.14159265359f;
	else if (dir == 'E')
		game->player_angle = 0.0f;
}
