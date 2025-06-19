#include "../../inc/cub3d.h"

void load_images(t_game *game)
{
    int image_w;
    int image_h;

    game->wall = mlx_xpm_file_to_image(game->mlx, "images/wall.xpm", &image_w, &image_h);
    game->player_img = mlx_xpm_file_to_image(game->mlx, "images/player.xpm", &image_w, &image_h);
    if(!game->player_img || !game->wall)
    {   
        ft_putstr_fd("Error loading images\n", 2);
        return ;
    }
}

void render_images(t_game *game, int x, int y)
{
    if(game->map[y][x] == '1')
        mlx_put_image_to_window(game->mlx, game->win, game->wall, x * TILE_SIZE, y * TILE_SIZE);
    else if(game->map[y][x] == 'P')
        mlx_put_image_to_window(game->mlx, game->win, game->player_img, x * TILE_SIZE, y * TILE_SIZE);
}
