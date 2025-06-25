#include "../../inc/cub3d.h"

void find_player(t_game *game)
{
    int x;
    int y;
    char cell;

    y = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width)
        {
            cell = game->map[y][x];
            if (cell == 'N' || cell == 'S' || cell == 'W' || cell == 'E')
            {
                game->player.tile_x = x;
                game->player.tile_y = y;
                game->player.position.x = x * TILE_SIZE + TILE_SIZE / 2;
                game->player.position.y = y * TILE_SIZE + TILE_SIZE / 2;
                set_player_angle(game, cell); // ← use the new function
                return;
            }
            x++;
        }
        y++;
    }
}


void set_player_angle(t_game *game, char dir)
{
    if (dir == 'N')
        game->player_angle = 4.71238898038f;  // 270° 
    else if (dir == 'S')
        game->player_angle = 1.57079632679f;  // 90°
    else if (dir == 'W')
        game->player_angle = 3.14159265359f;  // 180°
    else if (dir == 'E')
        game->player_angle = 0.0f;            // 0°   
}


void render_map(t_game *game)   
{
    mlx_clear_window(game->mlx, game->win);
    render_rays(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

int game_loop(t_game *game)
{

    render_map(game);
    return 0;
}

void game_hook(t_game *game)
{
    mlx_loop_hook(game.mlx, game_loop,  &game);
}