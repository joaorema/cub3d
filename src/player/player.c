#include "../../inc/cub3d.h"

void	user_input(t_game *game)
{
	mlx_key_hook(game->win, handle_keyboard, game);
}

int player_move(t_game *game, float m_x, float m_y)
{
    float new_x;
    float new_y;
    int map_x;
    int map_y;

    new_x = game->player_x + m_x;                               
    new_y = game->player_y + m_y;
    map_x = (int)(new_x) / TILE_SIZE;
    map_y = (int)(new_y) / TILE_SIZE;
    if(game->map[map_y][map_x] != '1')
    {
        game->player_x = new_x;
        game->player_y = new_y;
        mlx_clear_window(game->mlx, game->win);
        render_map(game);
        return 1;
    }
    return 0;
}


int	handle_keyboard(int keycode, t_game *game)
{
    float move_speed = 15.0; // Adjust as needed

    if (keycode == 65307)
        exit(1);
    if (keycode == 119) // W: forward
        player_move(game, cos(game->angle) * move_speed, sin(game->angle) * move_speed);
    if (keycode == 115) // S: backward
        player_move(game, -cos(game->angle) * move_speed, -sin(game->angle) * move_speed);
    if (keycode == 97)  // A: strafe left
        player_move(game, sin(game->angle) * move_speed, -cos(game->angle) * move_speed);
    if (keycode == 100) // D: strafe right
        player_move(game, -sin(game->angle) * move_speed, cos(game->angle) * move_speed);
    if (keycode == 65361 || keycode == 65363)
    {
        player_direction(keycode, game);
        mlx_clear_window(game->mlx, game->win);
        render_map(game);
    }
    return 0;
}

int player_direction(int keycode, t_game *game)
{
    if (keycode == 65361)                           // left move angle -0.1
        game->angle -= 0.1;
    if (keycode == 65363)                           // right move angle 0.1
        game->angle += 0.1;

    if (game->angle < 0)
        game->angle += 2 * PI;
    if (game->angle > 2 * PI)
        game->angle -= 2 * PI;

    game->player_dx = cos(game->angle);
    game->player_dy = sin(game->angle);
    
    return (0);
}