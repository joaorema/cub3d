#include "../../inc/cub3d.h"

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
int is_walkable(t_game *game, float x, float y)
{
    int map_x;
    int map_y;

    map_x = (int)floor(x / TILE_SIZE);
    map_y = (int)floor(y / TILE_SIZE);
    if (map_y < 0 || map_y >= game->map_height || map_x < 0 || map_x >= game->map_width)
        return 0;
    return (game->map[map_y][map_x] != '1');
}

int	handle_keyboard(int keycode, t_game *game)
{
    float angle;
    
    angle = game->player_angle;
    if (keycode == KEY_ESC)
        close_and_free(game, 0);
    if (keycode == KEY_W) // forward
        player_move(game, cos(angle) * MOVE_SPEED, sin(angle) * MOVE_SPEED);
    else if (keycode == KEY_S) // backward
        player_move(game, -cos(angle) * MOVE_SPEED, -sin(angle) * MOVE_SPEED);
    else if (keycode == KEY_A) // strafe left
        player_move(game, cos(angle - PI/2) * MOVE_SPEED, sin(angle - PI/2) * MOVE_SPEED);
    else if (keycode == KEY_D) // strafe right
        player_move(game, cos(angle + PI/2) * MOVE_SPEED, sin(angle + PI/2) * MOVE_SPEED);
    else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
        player_direction(keycode, game);

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

void	user_input(t_game *game)
{
    mlx_key_hook(game->win, handle_keyboard, game);
}