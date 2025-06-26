#include "../../inc/cub3d.h"

void h_sides(t_game *game, t_rayhit *hit)
{
   (void)game;
    hit->depth_of_field = hit->max_depth_of_field;
    hit->next_ray_x = hit->player_pos.x;
    hit->next_ray_y = hit->player_pos.y;
}
void h_up(t_game *game, t_rayhit *hit, float atan)
{
    (void)game;
    hit->next_ray_y = floor(hit->player_pos.y / TILE_SIZE) * TILE_SIZE - 0.0001f;
    hit->next_ray_x = (hit->player_pos.y - hit->next_ray_y) * atan + hit->player_pos.x;
    hit->y_offset = -TILE_SIZE;
    hit->x_offset = -hit->y_offset * atan;
}

void h_down(t_game *game, t_rayhit *hit, float atan)
{
    (void)game;
    hit->next_ray_y = floor(hit->player_pos.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
    hit->next_ray_x = (hit->player_pos.y - hit->next_ray_y) * atan + hit->player_pos.x;
    hit->y_offset = TILE_SIZE;
    hit->x_offset = -hit->y_offset * atan;
}

void update_hcheck(t_rayhit *hit)
{
    hit->next_ray_x += hit->x_offset;
    hit->next_ray_y += hit->y_offset;
    hit->depth_of_field++;
}
void final_hupdate(t_rayhit *hit)
{
    hit->hit_pos.x = hit->next_ray_x;
    hit->hit_pos.y = hit->next_ray_y;
    hit->distance = B_DISTANCE;
}
void hhit_wall(t_rayhit *hit)
{
    hit->hit_pos.x = hit->next_ray_x;
    hit->hit_pos.y = hit->next_ray_y;
    hit->distance = distance(
        hit->player_pos.x,
        hit->player_pos.y,
        hit->hit_pos.x,
        hit->hit_pos.y
    );
}

void h_s_tile(t_rayhit *hit)
{
    hit->map_x = (int)(hit->next_ray_x) / TILE_SIZE;
    hit->map_y = (int)(hit->next_ray_y) / TILE_SIZE;
}