/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:00:02 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/10 16:27:09 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void start_game(t_game *game)
{
    game->map = NULL;
    game->temp_map = NULL;
    game->player = 0;
    game->player_x = 0;
    game->player_y = 0;
    game->map_width = 0;
    game->map_height = 0;
    game->mlx = mlx_init();
    if(!game->mlx)
        exit(1);
    game->win = NULL;
    game->angle = 0.0f;
    game->player_dx = cos(game->angle) * 2;
    game->player_dy = sin(game->angle) * 2;
}

void init(t_game *game, char *file)
{
    start_game(game);
    count_height(game, file);
    count_width(game, file);
    game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE, game->map_height * TILE_SIZE, "Cub3d" );
    load_map(game, file);
    find_player(game);
    load_images(game);
    render_map(game);
}

void init_raystruct(t_game *game, t_rayhit *hit)
{
    hit->px = game->player_x;
    hit->py = game->player_y;
    hit->ra = game->angle;
    hit->dof = 0;
    hit->distance = 1000000;
    if(game->map_width > game->map_height)
        hit->max_dof = game->map_width;
    else
        hit->max_dof = game->map_height;
}

void init_rayhit(t_rayhit *hit, t_game *game, float angle)
{
    hit->ra = angle;
    hit->px = game->player_x;
    hit->py = game->player_y;
    if(game->map_width > game->map_height)
        hit->max_dof = game->map_width;
    else
        hit->max_dof = game->map_height;
}



