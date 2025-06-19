#include "../../inc/cub3d.h"

void	user_input(t_game *game)
{
	mlx_key_hook(game->win, handle_keyboard, game);
}

void	player_move(t_game *game, int dx, int dy)
{
    int new_x;
    int new_y;

    new_x = game->player_tile_x + dx;                               
    new_y = game->player_tile_y + dy;
    
    if(game->map[new_y][new_x] != '1')
    {
        game->map[game->player_tile_y][game->player_tile_x] = '0';
        game->player_tile_x = new_x;
        game->player_tile_y = new_y;
        game->map[new_y][new_x] = 'P';
        game->player_x = new_x * TILE_SIZE + TILE_SIZE / 2;
        game->player_y = new_y * TILE_SIZE + TILE_SIZE / 2;
        mlx_clear_window(game->mlx, game->win);
        render_map(game);
    }
}


int	handle_keyboard(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit(1);
	if (keycode == 119)
		player_move(game, 0, -1);
	if (keycode == 115)
		player_move(game, 0, 1);
	if (keycode == 97)
		player_move(game, -1, 0);
	if (keycode == 100)
		player_move(game, 1, 0);
    if (keycode == 65361 || keycode == 65363)
    {
        player_direction(keycode, game);
    }
    mlx_clear_window(game->mlx, game->win);
    render_map(game);
    return (0);
}

int player_direction(int keycode, t_game *game)
{
    if (keycode == 65361)                           // left move angle -0.1
        game->angle -= 0.1;
    if (keycode == 65363)                           // right move angle 0.1
        game->angle += 0.1;

    if (game->angle < 0)
        game->angle += 2 * PI;
    if (game->angle > 2 * PI)
        game->angle -= 2 * PI;

    game->player_dx = cos(game->angle);
    game->player_dy = sin(game->angle);
    
    return (0);
}