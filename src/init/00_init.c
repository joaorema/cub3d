/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:00:02 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/26 11:12:08 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_game(t_game *game)
{
	game->map = NULL;
	game->tmp_map = NULL;
	game->mlx = mlx_init();
	game->win = NULL;
	game->player_dir = '\0';
	game->player_pos.x = 0;
	game->player_pos.y = 0;
	game->map_width = 0;
	game->map_height = 0;
	game->map_inf.no_pth = NULL;
	game->map_inf.so_pth = NULL;
	game->map_inf.ea_pth = NULL;
	game->map_inf.we_pth = NULL;
	game->map_inf.c_rgb = NULL;
	game->map_inf.f_rgb = NULL;
	game->txt = NULL;
}

void	init_gnl(t_gnl *gnl)
{
	gnl->fd = -1;
	gnl->line = NULL;
}

void	init_ints(t_ints *ints)
{
	ints->i = -1;
	ints->j = -1;
	ints->x = 0;
	ints->z = 0;
}
