/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_check_walls_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:48:12 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/25 20:04:22 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	load_tmp_map(t_game *game)
{
	int		i;
	int		j;
	int		x;
	int		z;
	
	j = -1;
	i = -1;
	x = 0;
	game->tmp_map = calloc((game->map_height + 3), sizeof(char *));
	game->tmp_map[x] = calloc(game->map_width + 4, sizeof(char));
	while (++i < (game->map_width + 2))
		game->tmp_map[x][i] = 'X';
	game->tmp_map[x][++i] = '\0';
	j = -1;
	while(game->map[++j])
	{
		i = 0;
		game->tmp_map[++x] = calloc(game->map_width + 4, sizeof(char));
		game->tmp_map[x][i++] = 'X';
		z = 0;
		while (i < (game->map_width + 2))
		{
			if ((z >= (int)ft_strlen(game->map[j])) || ft_strchr(WS, game->map[j][z]))
				game->tmp_map[x][i] = 'X';
			else				
				game->tmp_map[x][i] = game->map[j][z];
			z++;
			i++;
		}
		game->tmp_map[x][++i] = '\0';
	}
	i = -1;
	game->tmp_map[++x] = calloc(game->map_width + 4, sizeof(char));
	while (++i < (game->map_width + 2))
		game->tmp_map[x][i] = 'X';
	game->tmp_map[x][++i] = '\0';
	game->tmp_map[++x] = NULL;
}

bool	ch_all_sides(t_game *game, int x, int y, char tg)
{
	if (game->tmp_map[y - 1][x] == tg || game->tmp_map[y][x - 1] == tg
		|| game->tmp_map[y + 1][x] == tg || game->tmp_map[y][x + 1] == tg)
		return (false);
	return (true);
}