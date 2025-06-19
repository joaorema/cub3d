#include "../../inc/cub3d.h"

void	close_and_free(t_game *game, int exit_code)
{
	if (game)
		free_game(game);
	exit (exit_code);
}

void	free_game(t_game *game)
{
	if (game && game->map)
		ft_free_array((void **)game->map);
	if (game && game->temp_map)
		ft_free_array((void **)game->temp_map);
	return ;
}
