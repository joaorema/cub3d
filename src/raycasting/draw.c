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
    //mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
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
    draw_topbottom(game, &wall);
}

void draw_topbottom(t_game *game, t_wall *wall)
{
    int x;
    int w;
    int y;
    unsigned int color;

    x = wall->screen_x;
    w = 0;
    while (w < wall->slice_width)
    {
        y = 0;
        while (y < (int)wall->wall_top && y < game->win_height)             // Draw sky
        {
            my_mlx_pixel_put(&game->img, x + w, y, SKY);
            y++;
        }
        while (y < (int)wall->wall_bottom && y < game->win_height)          // Draw wall
        {
            color = get_wall_tex_pixel(game, wall, y);
            my_mlx_pixel_put(&game->img, x + w, y, color);
            y++;
        }
        while (y < game->win_height)                                        // Draw floor
        {
            my_mlx_pixel_put(&game->img, x + w, y, FLOOR);
            y++;
        }
        w++;
    }
}


unsigned int get_wall_tex_pixel(t_game *game, t_wall *wall, int y)
{
    int wall_height;
    int tex_y;
    int tex_x;
    char *pixel;

    wall_height = wall->wall_bottom - wall->wall_top;
    if (wall_height <= 0)
        return 0;
    tex_y = ((y - wall->wall_top) * game->wall_img.height) / wall_height;
    if (tex_y >= game->wall_img.height)
        tex_y = game->wall_img.height - 1;
    tex_x = wall->tex_x;
    if (tex_x >= game->wall_img.width)
        tex_x = game->wall_img.width - 1;
    pixel = game->wall_img.addr + (tex_y * game->wall_img.line_len + tex_x * (game->wall_img.bits_per_pixel / 8));
    return *(unsigned int *)pixel;
}
