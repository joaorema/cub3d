#include "../../inc/cub3d.h"

void init_raystruct(t_game *game, t_rayhit *hit)
{
    hit->player_pos = game->player.position;
    hit->depth_of_field = 0;
    hit->distance = 1000000.0f;
    if(game->map_width > game->map_height)
        hit->max_depth_of_field = game->map_width;
    else
        hit->max_depth_of_field = game->map_height;
}

void init_rayhit(t_rayhit *hit, t_game *game, float angle)
{
    hit->player_pos = game->player.position;
    hit->ray_angle = angle;
    hit->depth_of_field = 0;
    hit->distance = 1000000.0f;
    if(game->map_width > game->map_height)
        hit->max_depth_of_field = game->map_width;
    else
        hit->max_depth_of_field = game->map_height;
}
