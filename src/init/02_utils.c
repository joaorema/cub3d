#include "../../inc/cub3d.h"

void init_map(t_game *game)
{
    game->map_inf.no_pth = NULL;
	game->map_inf.so_pth = NULL;
	game->map_inf.ea_pth = NULL;
	game->map_inf.we_pth = NULL;
	game->map_inf.c_rgb = NULL;
	game->map_inf.f_rgb = NULL;
}

void init_player(t_game *game)
{
    game->player.position.x = 0;
    game->player.position.y = 0;
    game->player.tile_x = 0;
    game->player.tile_y = 0;
    game->player.delta.x = 0;
    game->player.delta.y = 0;
    game->player.pixel_offset.x = 0;
    game->player.pixel_offset.y = 0;
    game->player_angle = 0.0f;
    game->player.delta.x = cos(game->player_angle) * 2;
    game->player.delta.y = sin(game->player_angle) * 2;
}

void init_images(t_game *game)
{
    game->img.img = mlx_new_image(game->mlx, game->win_width, game->win_height);
    game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
                                       &game->img.line_len, &game->img.endian);
    game->img.width = game->win_width;
    game->img.height = game->win_height;
    game->no_img.img = NULL;
    game->so_img.img = NULL;
    game->we_img.img = NULL;
    game->ea_img.img = NULL;
}