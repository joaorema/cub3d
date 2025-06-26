/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_game_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:17:16 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/26 14:17:28 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void init(t_game *game, char *file)
{
    init_game_struct(game);
    game->win_height = HEIGHT;
    game->win_width = WIDTH ;
    game->win = mlx_new_window(game->mlx, game->win_width, game->win_height, "Cub3d");
    load_and_parse_map(game, file);
    init_images(game);
    find_player(game);
    load_wall_images(game);
}

void render_map(t_game *game)   
{
    mlx_clear_window(game->mlx, game->win);
    render_rays(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

int game_loop(t_game *game)
{
    int moved;

    moved = move_player(game);
    if (moved || game->keys.left || game->keys.right) 
        render_map(game);
    return 0;
}

void handle_keys(t_game *game)
{
    mlx_hook(game->win, 2, (1L << 0), handle_keyboard, game);
    mlx_hook(game->win, 3, (1L << 1), key_released, game);
    mlx_hook(game->win, 17, (1L << 2), close_x, game);
}

void loop(t_game *game)
{
    mlx_loop_hook(game->mlx, game_loop,  game);
    mlx_loop(game->mlx);
}
