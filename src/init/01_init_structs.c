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
    hit->max_depth_of_field = 30;
}

void init_wall(t_game *game, t_rayhit *vhit, t_rayhit *hhit, t_wall *wall, float angle)
{
    float corrected_distance;
    float offset;

    check_distance(vhit, hhit, wall);
    wall->screen_center_y = game->win_height / 2;
    corrected_distance = wall->distance * cos(angle - game->player_angle);
    wall->projected_height = (TILE_SIZE * 320) / corrected_distance;
    set_wall(wall);
    if (wall->hit_vertical)
    {
        if (cos(angle) > 0)
            wall->side = EAST;
        else
            wall->side = WEST;
        offset = fmodf(wall->hit_point.y + 0.0001f, TILE_SIZE);
    }
    else
    {
        if (sin(angle) > 0)
            wall->side = SOUTH;
        else
            wall->side = NORTH;
        offset = fmodf(wall->hit_point.x + 0.0001f, TILE_SIZE);
    }
    wall->texture_x = (int)(offset / TILE_SIZE * game->no_img.width);
    if (wall->texture_x < 0)
        wall->texture_x = 0;
    if (wall->texture_x >= game->no_img.width)
        wall->texture_x = game->no_img.width - 1;
}

void set_wall(t_wall *wall)
{
    wall->top_pixel = wall->screen_center_y - wall->projected_height / 2;
    wall->bottom_pixel = wall->screen_center_y + wall->projected_height / 2;
}
//save difference and then use it later when printing

void check_distance(t_rayhit *vhit, t_rayhit *hhit, t_wall *wall)
{
    if (vhit->distance < hhit->distance)
    {
        wall->distance = vhit->distance;
        wall->hit_vertical = 1;
        wall->hit_point = vhit->hit_pos;
    }
    else
    {
        wall->distance = hhit->distance;
        wall->hit_vertical = 0;
        wall->hit_point = hhit->hit_pos;
    }
}