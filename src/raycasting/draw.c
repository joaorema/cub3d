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
    float x = game->player_x;
    float y = game->player_y;
    float dx = rx - x;
    float dy = ry - y;
    float steps = fabsf(dx) > fabsf(dy) ? fabsf(dx) : fabsf(dy);

    if (steps == 0)
        return;

    dx /= steps;
    dy /= steps;

    int i = 0;
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
    t_rayhit h_hit;
    t_rayhit v_hit;
    float r_angle;

    r_angle = game->angle;
    init_rayhit(&h_hit, game, r_angle);
    init_rayhit(&v_hit, game, r_angle);
    horizontal_check(game, &h_hit);
    vertical_check(game, &v_hit);

    if (h_hit.distance < v_hit.distance)
        draw_ray_line(game, h_hit.x, h_hit.y);
    else
        draw_ray_line(game, v_hit.x, v_hit.y);
}