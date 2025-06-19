#include "../../inc/cub3d.h"

void draw_line(t_game *game)
{
    int i;
    float x;
    float y;

    i = 0;
    y = game->player_y;
    x = game->player_x;
    while (i < 20)
    {
        x += game->player_dx * 2;
        y += game->player_dy * 2;
        mlx_pixel_put(game->mlx, game->win, (int)x, (int)y, 0xFF0000);
        i++;
    }
}

void draw_ray_line(t_game *game, float rx, float ry)
{
    float x;
    float y;
    float dx;
    float dy;
    float steps;
    int i;

    x = game->player_x;
    y = game->player_y;
    dx = rx - x;
    dy = ry - y;
    if(fabsf(dx) > fabsf(dy))
        steps = fabsf(dx);
    else
        steps = fabsf(dy);
    if (steps == 0)
        return;
    dx /= steps;
    dy /= steps;
    i = 0;
    while (i < (int)steps)
    {
        mlx_pixel_put(game->mlx, game->win, (int)x, (int)y, 0xFF0000);
        x += dx;
        y += dy;
        i++;
    }
}

void render_rays(t_game *game)
{
    int i;
    float ray_angle;
    t_rayhit v_hit;
    t_rayhit h_hit;

    i = 0;
    ray_angle = game->angle - (FOV / 2);
    while(i < NUM_RAYS)
    {
        init_rayhit(&v_hit, game, ray_angle);
        init_rayhit(&h_hit, game, ray_angle);
        horizontal_check(game, &h_hit);
        vertical_check(game, &v_hit);
        if (h_hit.distance < v_hit.distance)
            draw_ray_line(game, h_hit.x, h_hit.y);
        else
            draw_ray_line(game, v_hit.x, v_hit.y);
        ray_angle += ANGLE_STEP;
        if (ray_angle < 0)
            ray_angle += 2 * PI;
        if (ray_angle > 2 * PI)
            ray_angle -= 2 * PI;
        i++;
    }

}

void draw_circle(t_game *game, int cx, int cy, int radius, int color)
{
    int x, y;
    int r_sq = radius * radius;

    for (y = -radius; y <= radius; y++)
    {
        for (x = -radius; x <= radius; x++)
        {
            if (x*x + y*y <= r_sq) // inside the circle radius
            {
                mlx_pixel_put(game->mlx, game->win, cx + x, cy + y, color);
            }
        }
    }
}
