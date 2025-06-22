#include "../../inc/cub3d.h"

void render_rays(t_game *game)
{
    int i;
    float ray_angle;

    i = 0;
    ray_angle = game->player_angle - (FOV / 2);
    while (i < NUM_RAYS)
    {
        render_wall(game, ray_angle, i);
        ray_angle += ANGLE_STEP;

        if (ray_angle < 0)
            ray_angle += 2 * PI;
        if (ray_angle > 2 * PI)
            ray_angle -= 2 * PI;

        i++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void render_wall(t_game *game, float angle, int ray_index)
{
    t_rayhit v_hit;
    t_rayhit h_hit;
    t_wall wall;

    init_rayhit(&v_hit, game, angle);
    init_rayhit(&h_hit, game, angle);
    horizontal_check(game, &h_hit);
    vertical_check(game, &v_hit);
    wall.screen_x = (int)((float)ray_index / NUM_RAYS * game->win_width);
    wall.slice_width = game->win_width / NUM_RAYS;
    init_wall(game, &v_hit, &h_hit, &wall, angle);
    draw_topbottom(game, &wall);
    draw_wall_slice(game, &wall);
}

void draw_topbottom(t_game *game, t_wall *wall)
{
    int x;
    int w;
    int sky_height;
    int floor_height;

    x = wall->screen_x;
    w = 0;
    while (w < wall->slice_width)
    {
        sky_height = (int)wall->top_pixel;
        floor_height = game->win_height - (int)wall->bottom_pixel;
        if (sky_height > 0)                                                            // Draw sky rectangle for this vertical slice
            draw(&game->img, (t_point){x + w, 0}, (t_point){1, sky_height}, SKY);
        if (floor_height > 0)                                                          // Draw floor rectangle for this vertical slice
            draw(&game->img, (t_point){x + w, (int)wall->bottom_pixel}, (t_point){1, floor_height}, FLOOR);
        w++;
    }
}

void draw_wall_slice(t_game *game, t_wall *wall)
{
    int x = wall->screen_x;
    int w = 0;
    unsigned int color;
    int y_start = (int)wall->top_pixel;
    int y_end = (int)wall->bottom_pixel;

    while (w < wall->slice_width)
    {
        for (int y = y_start; y < y_end && y < game->win_height; y++)
        {
            color = get_wall_tex_pixel(game, wall, y);
            my_mlx_pixel_put(&game->img, x + w, y, color);
        }
        w++;
    }
}

unsigned int get_wall_tex_pixel(t_game *game, t_wall *wall, int y)
{
    int tex_y;
    int tex_x = wall->texture_x;
    char *pixel;

    int wall_height = wall->bottom_pixel - wall->top_pixel;
    if (wall_height <= 0)
        return 0;

    float sample_ratio = (float)(y - wall->top_pixel) / (float)wall_height;
    if (sample_ratio < 0.0f)
        sample_ratio = 0.0f;
    else if (sample_ratio > 1.0f)
        sample_ratio = 1.0f;

    tex_y = (int)(sample_ratio * (game->wall_img.height - 1));

    // Clamp values for safety
    if (tex_y < 0)
        tex_y = 0;
    else if (tex_y >= game->wall_img.height)
        tex_y = game->wall_img.height - 1;

    if (tex_x < 0)
        tex_x = 0;
    else if (tex_x >= game->wall_img.width)
        tex_x = game->wall_img.width - 1;

    pixel = game->wall_img.addr + (tex_y * game->wall_img.line_len + tex_x * (game->wall_img.bits_per_pixel / 8));

    return *(unsigned int *)pixel;
}



void	draw(t_image *image, t_point pos, t_point size, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			my_mlx_pixel_put(image, pos.x + x, pos.y + y++, color);
		}
		x++;
	}
}
