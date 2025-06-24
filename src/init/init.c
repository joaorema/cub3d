
#include "../../inc/cub3d.h"

void start_game(t_game *game)
{
    game->map = NULL;
    game->map_width = 0;
    game->map_height = 0;
    game->win_width = 0;
    game->win_height = 0;
    game->player.position.x = 0;
    game->player.position.y = 0;
    game->player.tile_x = 0;
    game->player.tile_y = 0;
    game->player.delta.x = 0;
    game->player.delta.y = 0;
    game->player.pixel_offset.x = 0;
    game->player.pixel_offset.y = 0;
    game->player_angle = 0.0f;
    game->mlx = mlx_init();
    if (!game->mlx)
        exit(1);
    game->win = NULL;
    game->player.delta.x = cos(game->player_angle) * 2;
    game->player.delta.y = sin(game->player_angle) * 2;
}




void init(t_game *game, char *file)
{
    start_game(game);
    count_height(game, file);
    count_width(game, file);
    game->win_height = game->map_height * TILE_SIZE;
    game->win_width = game->map_width * TILE_SIZE;
    game->win = mlx_new_window(game->mlx, game->win_width, game->win_height, "Cub3d");
    game->img.img = mlx_new_image(game->mlx, game->win_width, game->win_height);
    game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_len, &game->img.endian);
    game->img.width = game->win_width;
    game->img.height = game->win_height;
    load_map(game, file);
    find_player(game);
    load_wall_image(game);
}

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
    set_wall(game, wall);
    if (wall->hit_vertical)
        offset = fmodf(wall->hit_point.y + 0.0001f, TILE_SIZE);
    else
        offset = fmodf(wall->hit_point.x + 0.0001f, TILE_SIZE);
    wall->texture_x = (int)(offset / TILE_SIZE * game->wall_img.width);
    if (wall->texture_x < 0)
        wall->texture_x = 0;
    if (wall->texture_x >= game->wall_img.width)
        wall->texture_x = game->wall_img.width - 1;
}


void set_wall(t_game *game, t_wall *wall)
{
    wall->top_pixel = wall->screen_center_y - wall->projected_height / 2;
    wall->bottom_pixel = wall->screen_center_y + wall->projected_height / 2;
    if (wall->top_pixel < 0)
        wall->top_pixel = 0;
    if (wall->bottom_pixel > game->win_height)
        wall->bottom_pixel = game->win_height;
    
}


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