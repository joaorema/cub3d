/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:30:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/25 00:47:09 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	char_is_valid(char c)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != '1' && c != '0'  && c != ' ')
		return (false);
	return(true);
}

void	set_pl_info(t_game *game, char c, int x, int y)
{
	game->player_dir = c;
	game->player_x = x;
	game->player_y = y;
}

void	load_tmp_map(t_game *game)
{
	int		i;
	int		j;
	int		x;
	int		z;
	
	j = -1;
	i = -1;
	x = -1;
	game->tmp_map = malloc(sizeof(char *) * (game->map_height + 3));
	game->tmp_map[++x] = calloc(game->map_width + 3, sizeof(char));
	while (++i < (game->map_width + 1))
		game->tmp_map[x][i] = 'X';
	game->tmp_map[x][++i] = '\0';
	j = -1;
	while(game->map[++j])
	{
		i = 0;
		game->tmp_map[++x] = calloc(game->map_width + 3, sizeof(char));
		game->tmp_map[x][i++] = 'X';
		z = 0;
		while (i < (game->map_width + 1))
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
	game->tmp_map[++x] = calloc(game->map_width + 3, sizeof(char));
	while (++i < (game->map_width + 1))
		game->tmp_map[x][i] = 'X';
	game->tmp_map[x][++i] = '\0';
	game->tmp_map[++x] = NULL;
}
