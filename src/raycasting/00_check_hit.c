#include "../../inc/cub3d.h"

void horizontal_check(t_game *game, t_rayhit *hit)
{
    float ray_angle;
    float atan_angle; 

    init_raystruct(game, hit);
    ray_angle = hit->ray_angle;
    atan_angle = -1 / tan(ray_angle);
    if (ray_angle == 0 || ray_angle == PI)                  // Looking exactly left or right
        h_sides(game, hit);
    else if (ray_angle > PI)                                // Looking up
        h_up(game, hit, atan_angle);
    else if (ray_angle < PI)                                // Looking down
        h_down(game, hit, atan_angle);
    while (hit->depth_of_field < hit->max_depth_of_field)
    {
        h_s_tile(hit);
        if (hit->map_x >= 0 && hit->map_x < game->map_width &&
            hit->map_y >= 0 && hit->map_y < game->map_height &&
            game->map[hit->map_y][hit->map_x] == '1')
        {
            hhit_wall(hit, ray_angle);
            return;
        }
        update_hcheck(hit);
    }
    final_hupdate(hit);
}

void vertical_check(t_game *game, t_rayhit *hit)
{
    float ray_angle;
    float ntan_angle;

    init_raystruct(game, hit);
    ray_angle = hit->ray_angle;
    ntan_angle = -tan(ray_angle);
    if (ray_angle == P2 || ray_angle == P3) // Looking exactly up or down
        v_top_down(game, hit);
    else if (ray_angle < P2 || ray_angle > P3) // Looking right
        v_right(game, hit, ntan_angle);
    else if (ray_angle > P2 && ray_angle < P3) // Looking left
        v_left(game, hit, ntan_angle);
    while (hit->depth_of_field < hit->max_depth_of_field)
    {
        v_s_tile(hit);
        if (hit->map_x >= 0 && hit->map_x < game->map_width &&
            hit->map_y >= 0 && hit->map_y < game->map_height &&
            game->map[hit->map_y][hit->map_x] == '1')
        {
            vhit_wall(hit, ray_angle);
            return;
        }
        update_vcheck(hit);
    }
    final_vupdate(hit);
}
