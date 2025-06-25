/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_check_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:45:36 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/25 19:37:59 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ch_closed_walls(t_game *game, char **tmp_map, int max_y,  int max_x)
{
	t_point start_pos;
	
	start_pos = prep_chars(tmp_map, max_y ,max_x);
	print_tmp_map(game, 2, &start_pos); //debug to delete
	flood_fill(game, start_pos,'0');
	print_tmp_map(game, 3, NULL); //debug to delete
	ch_islands(game, tmp_map, max_y, max_x);
}

t_point	prep_chars(char **tmp_map, int max_y, int max_x)
{
	t_point	start_pos;
	bool	ch_start_pos;
	int	x;
	int y;

	y = -1;
	ch_start_pos = false;
	while (++y < max_y)
	{
		x = -1;
		while(++x < max_x)
		{
			if (!ch_start_pos && (tmp_map[y][x] != '1' && tmp_map[y][x] != 'X'))
			{
				start_pos.x = x;
				start_pos.y = y;
				ch_start_pos = true;
			}
			if (play_char(tmp_map[y][x]))
				tmp_map[y][x] = '0';
		}
	}
	return (start_pos);
}

void	flood_fill(t_game *game, t_point start_pos, char tg)
{
	t_point new_pos;

	if (start_pos.x < 0 || start_pos.x >= (game->map_width + 1)
		|| start_pos.y < 0 || start_pos.y >= (game->map_height + 1))
		return ;
	if (game->tmp_map[start_pos.y][start_pos.x] != tg)
		return ;
	game->tmp_map[start_pos.y][start_pos.x] = 'F';
	new_pos = (t_point){start_pos.x + 1, start_pos.y};
	flood_fill(game, new_pos, tg);
	new_pos = (t_point){start_pos.x - 1, start_pos.y};
	flood_fill(game, new_pos, tg);
	new_pos = (t_point){start_pos.x, start_pos.y + 1};
	flood_fill(game, new_pos, tg);
	new_pos = (t_point){start_pos.x, start_pos.y - 1};
	flood_fill(game, new_pos, tg);
}

void	ch_islands(t_game *game, char **tmp_map, int max_y, int max_x)
{
	int	x;
	int y;

	y = 0;
	while (++y < max_y)
	{
		x = 0;
		while(++x < max_x)
		{
			if (tmp_map[y][x] == '0' || tmp_map[y][x] == 'F')
			{
				if (!ch_all_sides(game, x, y, 'X'))
					print_err_and_exit(game, RED ERR OPMAP RESET, 2);
			}
			if (tmp_map[y][x] == 'X')
			{
				if (!ch_all_sides(game, x, y, 'F'))
					print_err_and_exit(game, RED ERR SPMAP RESET, 2);
			}
		}
	}
}
