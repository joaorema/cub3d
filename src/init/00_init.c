/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:00:02 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/20 14:44:55 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void  init_game(t_game *game)
{
	game->map = NULL;
	game->tmp_map = NULL;
	game->mlx = NULL;
	game->win = NULL;
	game->player = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->map_width = 0;
	game->map_height = 0;
	game->map_inf.no_pth = NULL;
	game->map_inf.so_pth = NULL;
	game->map_inf.ea_pth = NULL;
	game->map_inf.we_pth = NULL;
	game->map_inf.c_rgb = NULL;
	game->map_inf.f_rgb = NULL;
}
