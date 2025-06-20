#include "../../inc/cub3d.h"

void render_rays(t_game *game)
{
    int i;
    float ray_angle;

    i = 0;
    ray_angle = game->angle - (FOV / 2);
    while(i < NUM_RAYS)
    {
        render_wall(game, ray_angle, i);
        ray_angle += ANGLE_STEP;
        if (ray_angle < 0)
            ray_angle += 2 * PI;
        if (ray_angle > 2 * PI)
            ray_angle -= 2 * PI;
        i++;
    }
}

void render_wall(t_game *game, float angle, int col)
{
    t_rayhit v_hit;
    t_rayhit h_hit;
    t_wall wall;

    init_rayhit(&v_hit, game, angle);
    init_rayhit(&h_hit, game, angle);
    horizontal_check(game, &h_hit);
    vertical_check(game, &v_hit);
    wall.screen_x = (col * game->win_width) / NUM_RAYS;
    init_wall(game, &v_hit, &h_hit, &wall);
    draw_wall(game, &wall);
}

void draw_wall(t_game *game, t_wall *wall)
{
    wall->w = 0;
    while (wall->w < wall->slice_width)
    {
        wall->y = (int)wall->wall_top;
        while (wall->y < (int)wall->wall_bottom)
        {
            mlx_pixel_put(game->mlx, game->win, wall->screen_x + wall->w, wall->y, RED);
            wall->y++;
        }
        wall->w++;
    }
}

