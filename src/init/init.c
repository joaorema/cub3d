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

t_game  start_game(t_game *game)
{
    game->map = NULL;
    game->temp_map = NULL;
    game->player = 0;
    game->player_x = 0;
    game->player_y = 0;
    game->map_width = 0;
    game->map_height = 0;
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, 800, 600, "cub3d");
    return (*game);

}

void load_images(t_game *game, int x, int y)
{
    int image_w;
    int image_h;

    game->player_img = mlx_xpm_file_to_image(game->mlx, "images/player.xpm", &image_w, &image_h);
    if(!game->player_img)
    {   
        ft_putstr_fd("Error loading images\n", 2);
        return ;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->player_img, x * TILE_SIZE, y * TILE_SIZE);
}


int	handle_keyboard(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit(1);
	if (keycode == 119 || keycode == 65362)
		player_move(game, 0, -1);
	if (keycode == 115 || keycode == 65364)
		player_move(game, 0, 1);
	if (keycode == 97 || keycode == 65361)
		player_move(game, -1, 0);
	if (keycode == 100 || keycode == 65363)
		player_move(game, 1, 0);
	return (0);
}

void	player_move(t_game *game, int dx, int dy)
{
	game->player_x = game->player_x + dx;
	game->player_y = game->player_y + dy;
    update_player(game);
}

void	user_input(t_game *game)
{
	mlx_key_hook(game->win, handle_keyboard, game);
    
}

void update_player(t_game *game)
{
    mlx_clear_window(game->mlx, game->win);    //clear window
    mlx_put_image_to_window(game->mlx, game->win, game->player_img, game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);

}