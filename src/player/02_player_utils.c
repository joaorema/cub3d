#include "../../inc/cub3d.h"

static int is_blocked_at(t_game *game, float x, float y)
{
    int map_x;
    int map_y;

    map_x = (int)floor(x / TILE_SIZE);
    map_y = (int)floor(y / TILE_SIZE);
    if (map_y < 0 || map_y >= game->map_height || map_x < 0 || map_x >= game->map_width)
        return 1;
    if (game->map[map_y][map_x] == '1')
        return 1;
    return 0;
}

int is_walkable(t_game *game, float x, float y)
{
    float r;

    r = P_RADIUS;
    if (is_blocked_at(game, x, y + r)) 
        return 0;
    if (is_blocked_at(game, x, y - r)) 
        return 0;
    if (is_blocked_at(game, x + r, y)) 
        return 0;
    if (is_blocked_at(game, x - r, y)) 
        return 0;
    return 1;
}
int move_player(t_game *game)
{
    float angle;
    int moved;

    angle = game->player_angle;
    moved = 0;
    if (game->keys.w) 
        moved |= player_move(game, cos(angle) * MOVE_SPEED, sin(angle) * MOVE_SPEED);
    if (game->keys.s) 
        moved |= player_move(game, -cos(angle) * MOVE_SPEED, -sin(angle) * MOVE_SPEED);
    if (game->keys.a) 
        moved |= player_move(game, cos(angle - PI / 2) * MOVE_SPEED, sin(angle - PI / 2) * MOVE_SPEED);
    if (game->keys.d) 
        moved |= player_move(game, cos(angle + PI / 2) * MOVE_SPEED, sin(angle + PI / 2) * MOVE_SPEED);
    if (game->keys.left)
        rotate_player(game, -ROT_SPEED);
    if (game->keys.right)
        rotate_player(game, ROT_SPEED);
    return moved;
}
