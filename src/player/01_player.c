#include "../../inc/cub3d.h"

int	handle_keyboard(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        close_and_free(game, 0);
    else if(keycode == KEY_W) 
        game->keys.w = 1;
    else if (keycode == KEY_S) 
        game->keys.s = 1;
    else if (keycode == KEY_A) 
        game->keys.a = 1;
    else if (keycode == KEY_D) 
        game->keys.d = 1;
    else if (keycode == KEY_LEFT)
        game->keys.left = 1;
    else if (keycode == KEY_RIGHT) 
        game->keys.right = 1;
    return 0;
}

int key_released(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        game->keys.w = 0;
    else if (keycode == KEY_A)
        game->keys.a = 0;
    else if (keycode == KEY_S)
        game->keys.s = 0;
    else if (keycode == KEY_D)
        game->keys.d = 0;
    else if (keycode == KEY_LEFT)
        game->keys.left = 0;
    else if (keycode == KEY_RIGHT)
        game->keys.right = 0;
    return 0;
}

int player_direction(int keycode, t_game *game)
{
    if (keycode == KEY_LEFT)
        game->player_angle -= 0.1f;
    if (keycode == KEY_RIGHT)
        game->player_angle += 0.1f;
    if (game->player_angle < 0)
        game->player_angle += 2 * PI;
    if (game->player_angle > 2 * PI)
        game->player_angle -= 2 * PI;
    game->player.delta.x = cos(game->player_angle);
    game->player.delta.y = sin(game->player_angle);
    return 0;
}
int player_move(t_game *game, float dx, float dy)
{
    float new_x;
    float new_y;

    new_x = game->player.position.x + dx;
    new_y = game->player.position.y + dy;
    if (is_walkable(game, new_x, new_y))
    {
        game->player.position.x = new_x;
        game->player.position.y = new_y;
        return 1;
    }
    return 0;
}

void rotate_player(t_game *game, float rotation)
{
    game->player_angle += rotation;
    
    if (game->player_angle < 0)
        game->player_angle += 2 * PI;
    if (game->player_angle > 2 * PI)
        game->player_angle -= 2 * PI;

    game->player.delta.x = cos(game->player_angle);
    game->player.delta.y = sin(game->player_angle);
}