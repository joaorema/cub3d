
#include "../../inc/cub3d.h"

void start_game(t_game *game)
{
    game->map = NULL;
    game->tmp_map = NULL;
    init_map(game);
    game->txt = NULL;
    game->player_direction = '\0';
    game->map_width = 0;
    game->map_height = 0;
    game->win_width = 0;
    game->win_height = 0;
    init_player(game);
    init_keys(game);
    game->mlx = mlx_init();
    game->win = NULL;
}

void init(t_game *game, char *file)
{
    start_game(game);
    game->win_height = HEIGHT;
    game->win_width = WIDTH ;
    game->win = mlx_new_window(game->mlx, game->win_width, game->win_height, "Cub3d");
    init_images(game);
    load_and_parse_map(game, file);
    find_player(game);
    load_wall_images(game);
}


