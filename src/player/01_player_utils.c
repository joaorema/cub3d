/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   01_player_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:28:55 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/26 18:00:05 by icunha-t         ###   ########.fr       */
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
		x = 0;
		while (x < game->map_width)
		{
			cell = game->map[y][x];
			if (cell == 'N' || cell == 'S' || cell == 'W' || cell == 'E')
			{
				game->player.tile_x = x;
				game->player.tile_y = y;
				game->player.position.x = x * TILE_SIZE + TILE_SIZE / 2;
				game->player.position.y = y * TILE_SIZE + TILE_SIZE / 2;
				set_player_angle(game, cell);
				return ;
			}
			x++;
		}
		y++;
	}
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

static int	is_blocked_at(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)floor(x / TILE_SIZE);
	map_y = (int)floor(y / TILE_SIZE);
	if (map_y < 0 || map_y >= game->map_height || map_x < 0
		|| map_x >= game->map_width)
		return (1);
	if (game->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	is_walkable(t_game *game, float x, float y)
{
	float	r;

	r = P_RADIUS;
	if (is_blocked_at(game, x, y + r))
		return (0);
	if (is_blocked_at(game, x, y - r))
		return (0);
	if (is_blocked_at(game, x + r, y))
		return (0);
	if (is_blocked_at(game, x - r, y))
		return (0);
	return (1);
}

int	move_player(t_game *game)
{
	float	angle;
	int		moved;

	angle = game->player_angle;
	moved = 0;
	if (game->keys.w)
		moved |= player_move(game, cos(angle) * MOVE_SPEED,
				sin(angle) * MOVE_SPEED);
	if (game->keys.s)
		moved |= player_move(game, -cos(angle) * MOVE_SPEED,
				-sin(angle) * MOVE_SPEED);
	if (game->keys.a)
		moved |= player_move(game, cos(angle - PI / 2) * MOVE_SPEED,
				sin(angle - PI / 2) * MOVE_SPEED);
	if (game->keys.d)
		moved |= player_move(game, cos(angle + PI / 2) * MOVE_SPEED,
				sin(angle + PI / 2) * MOVE_SPEED);
	if (game->keys.left)
		rotate_player(game, -ROT_SPEED);
	if (game->keys.right)
		rotate_player(game, ROT_SPEED);
	return (moved);
}
