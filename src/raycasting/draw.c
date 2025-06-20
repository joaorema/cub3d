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
    draw_column(game, &wall);
}

void draw_column(t_game *game, t_wall *wall)
{
    int x;
    int w;
    int y;

    x = wall->screen_x;
    w = 0;
    while (w < wall->slice_width)
    {
        y = 0;
        while (y < (int)wall->wall_top && y < game->win_height)             // Draw sky
        {
            mlx_pixel_put(game->mlx, game->win, x + w, y, SKY);
            y++;
        }
        while (y < (int)wall->wall_bottom && y < game->win_height)          // Draw wall
        {
            mlx_pixel_put(game->mlx, game->win, x + w, y, BRICKRED);
            y++;
        }
        while (y < game->win_height)                                        // Draw floor
        {
            mlx_pixel_put(game->mlx, game->win, x + w, y, FLOOR);
            y++;
        }
        w++;
    }
}
