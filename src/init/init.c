
#include "../../inc/cub3d.h"

void start_game(t_game *game)
{
    game->map = NULL;
    game->player.player = 0;
    game->player.player_x = 0;
    game->player.player_y = 0;
    game->map_width = 0;
    game->map_height = 0;
    game->win_height = 0;
    game->win_width = 0;
    game->mlx = mlx_init();
    if(!game->mlx)
        exit(1);
    game->win = NULL;
    game->angle = 0.0f;
    game->player.player_dx = cos(game->angle) * 2;
    game->player.player_dy = sin(game->angle) * 2;
}



void init(t_game *game, char *file)
{
    start_game(game);
    count_height(game, file);
    count_width(game, file);
    game->win_height = game->map_height * TILE_SIZE;
    game->win_width = game->map_width * TILE_SIZE;
    game->win = mlx_new_window(game->mlx, game->win_width, game->win_height, "Cub3d" );
    game->img.img = mlx_new_image(game->mlx, game->win_width, game->win_height);
    game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_len, &game->img.endian);
    load_map(game, file);
    find_player(game);
    //render_map(game);
}

void init_raystruct(t_game *game, t_rayhit *hit)
{
    hit->px = game->player.player_x;
    hit->py = game->player.player_y;
    hit->dof = 0;
    hit->distance = 1000000;
    if(game->map_width > game->map_height)
        hit->max_dof = game->map_width;
    else
        hit->max_dof = game->map_height;
}

void init_rayhit(t_rayhit *hit, t_game *game, float angle)
{
    hit->px = game->player.player_x;
    hit->py = game->player.player_y;
    hit->ra = angle;
    hit->dof = 0;
    hit->max_dof = 30; 
}

void init_wall(t_game *game, t_rayhit *vhit, t_rayhit *hhit, t_wall *wall)
{
    wall->screen_center = game->win_height / 2;
    if(vhit->distance < hhit->distance)
        wall->wall_dist = vhit->distance;
    else
        wall->wall_dist = hhit->distance;
    wall->lineh = (TILE_SIZE * 320) / wall->wall_dist;
    wall->wall_top = wall->screen_center - wall->lineh / 2;
    wall->wall_bottom = wall->screen_center + wall->lineh / 2;
    wall->slice_width = game->win_width / NUM_RAYS;
}


