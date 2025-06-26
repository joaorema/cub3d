/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_check_wall_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:24:03 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/26 14:25:23 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	load_tmp_map(t_game *game)
{
	t_ints ints;
	
	init_ints(&ints);
	game->tmp_map = calloc((game->map_height + 3), sizeof(char *));
	game->tmp_map[ints.x] = calloc(game->map_width + 4, sizeof(char));
	add_extra_line(game, &ints, 0);
	while(game->map[++(ints.j)])
	{
		ints.i = 0;
		game->tmp_map[++(ints.x)] = calloc(game->map_width + 4, sizeof(char));
		game->tmp_map[ints.x][ints.i++] = 'X';
		ints.z = 0;
		while (ints.i < (game->map_width + 2))
		{
			if ((ints.z >= (int)ft_strlen(game->map[ints.j]))
				|| ft_strchr(WS, game->map[ints.j][ints.z]))
				game->tmp_map[ints.x][ints.i] = 'X';
			else				
				game->tmp_map[ints.x][ints.i] = game->map[ints.j][ints.z];
			incr_ints(&ints.z, &ints.i);
		}
		game->tmp_map[ints.x][++(ints.i)] = '\0';
	}
	game->tmp_map[++(ints.x)] = calloc(game->map_width + 4, sizeof(char));
	add_extra_line(game, &ints, 1);
}

void add_extra_line(t_game *game, t_ints *ints, int n)
{
	ints->i = -1;

	while (++(ints)->i < (game->map_width + 2))
		game->tmp_map[ints->x][ints->i] = 'X';
	game->tmp_map[ints->x][++(ints->i)] = '\0';
	if (n == 1)
		game->tmp_map[++(ints->x)] = NULL;
}

void	incr_ints(int *z, int *i)
{
	(*z)++;
	(*i)++;
}

bool	ch_all_sides(t_game *game, int x, int y, char tg)
{
	if (game->tmp_map[y - 1][x] == tg || game->tmp_map[y][x - 1] == tg
		|| game->tmp_map[y + 1][x] == tg || game->tmp_map[y][x + 1] == tg)
		return (false);
	return (true);
}
